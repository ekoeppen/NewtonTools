#!/usr/local/bin/luacheia5

require ("frames.lua")

-- Utility functions -----------------------------------------------------------

function getHex (s, i)
	local c1, c2
	
	c1 = string.byte (s, i) - 48; if c1 > 9 then c1 = c1 - 39; end
	c2 = string.byte (s, i + 1) - 48; if c2 > 9 then c2 = c2 - 39; end
	return c1 * 16 + c2;
end

function intToBuffer (n)
	return 
		string.char (bit.band (bit.rshift (n, 24), 255)) ..
		string.char (bit.band (bit.rshift (n, 16), 255)) ..
		string.char (bit.band (bit.rshift (n, 8), 255)) ..
		string.char (bit.band (n, 255))
end

-- Get binary data -------------------------------------------------------------

function getTextSegment (file)
	local hex, data, line
	
	hex = ""
	os.execute ("/usr/local/bin/arm-elf-readelf -x 1 " .. file .. " > /tmp/dump");
	for line in io.lines ("/tmp/dump") do
		if string.sub (line, 1, 4) == "  0x" then
			hex = hex .. string.gsub (string.sub (line, 14, 48), "%s", "");
		end
	end

	data = "";
	for i = 1, string.len(hex), 2 do
		data = data .. string.char(getHex (hex, i));
	end
	
	return data
end

function getRelocations (file)
	local n, relocs, data, i, v, line
	
	n = 0
	relocs = {}
	os.execute ("/usr/local/bin/arm-elf-objdump -r " .. file .. " > /tmp/dump");
	for line in io.lines ("/tmp/dump") do
		if string.sub(line, 10, 20) == "R_ARM_ABS32" then
			n = n + 1
			relocs[n] = tonumber (string.sub (line, 1, 9), 16)
		end
	end

	data = intToBuffer (n)
	for i, v in ipairs (relocs) do
		data = data .. intToBuffer (relocs[i])
	end
	return data
end

function getEntryPoints (file, entryPoints)
	local entries, i, v, j, k, line, names
	
	os.execute ("/usr/local/bin/arm-elf-nm " .. file .. " > /tmp/dump");
	for line in io.lines ("/tmp/dump") do
		for i, v in entryPoints do
			if string.sub(line, 10) == "T " ..  entryPoints[i].name then
				entryPoints[i].offset = tonumber (string.sub (line, 1, 9), 16)
			end
		end
	end

	entries = Array:new({})
	for i, v in entryPoints do
		entries[i] = Frame:new({
			name = Symbol:new (v.name),
			offset = Integer:new (v.offset),
			numArgs = Integer:new (v.numArgs)
		})
	end
	
	return entries
end

-- Parse entry point spec ------------------------------------------------------

function parseEntryPoints (entryString)
	local f, i, v, n, r
	
	n = 0
	r = {}
	f = string.gfind (entryString, "([^%s\(]*)%s*%(%s*([%d]*)%s*%)")
	for i, v in f do
		n = n + 1
		r[n] = {name = i, offset = 0, numArgs = tonumber(v, 10)}
	end
	return r
end

-- Create frame ----------------------------------------------------------------

function createFrame (file, moduleName, entryPoints)
	local f, data, entries, i, v
	
	data = getTextSegment (file)
	relocs = getRelocations (file)
	entries = getEntryPoints (file, parseEntryPoints (entryPoints))
	f = Frame:new({
		version		= Integer:new (1),
		class 		= Symbol:new ("NativeModule"),
		CPUType 	= Symbol:new ("ARM610"),
		debugFile	= Symbol:new ("f.sym"),
		name		= Symbol:new (moduleName),
		code		= Binary:new (data, "code"),
		relocations	= Binary:new (relocs, "relocs"),
		entryPoints	= entries
	})
	
	return f;
end

-- Dump frame ------------------------------------------------------------------

function fileToNtkc (fileName, output, moduleName, entryPoints)
	local f, encode, file

	f = createFrame (fileName, moduleName, entryPoints)
	
	encode = "\2"
	encode = encode .. f:encode ()
	
	file = io.open (output, "w+");
	file:write (encode);
	file:close ();
	
	os.execute ("/Developer/Tools/SetFile -t \"ntkc\" -c \"NTP1\" " .. output)
end

-- Main ------------------------------------------------------------------------

fileToNtkc (arg[1], arg[2], arg[3], arg[4])
