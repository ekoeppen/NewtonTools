#!/usr/local/bin/luacheia5

cheia.load ("bit")
require ("/Library/NewtonTools/bin/frames.lua")

function typeof (o)
	return getmetatable (o)
end

-- Pointer ----------------------------------------------------------------------

Pointer = {_type = "Pointer"}

function Pointer:new (v)
	f = {value = v}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Pointer:tostring ()
	return "#" .. self.value
end

function Pointer:print (indent)
	print (string.rep (" ", indent * 4) .. "#" .. self.value)
end

function Pointer:encode ()
	local d
	
	return d
end

-- MagicPointer ------------------------------------------------------------------

MagicPointer = {_type = "MagicPointer"}

function MagicPointer:new (v)
	f = {value = v}
	setmetatable (f, self)
	self.__index = self
	return f
end

function MagicPointer:tostring ()
	return "@" .. self.value
end

function MagicPointer:print (indent)
	print (string.rep (" ", indent * 4) .. "@" .. self.value)
end

function MagicPointer:encode ()
	local d
	
	return d
end

-- Character -------------------------------------------------------------------

Character = {_type = "Character"}

function Character:new (v)
	f = {value = v}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Character:tostring ()
	return self.value
end

function Character:print (indent)
	print (string.rep (" ", indent * 4) .. self.value)
end

function Character:encode ()
	local d
	
	return d
end

-- Immediate -------------------------------------------------------------------

Immediate = {_type = "Immediate"}

function Immediate:new (v)
	f = {value = v}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Immediate:tostring ()
	return tostring (self.value)
end

function Immediate:print (indent)
	if not self.value then print (string.rep (" ", indent * 4) .. "nil")
	else print (string.rep (" ", indent * 4) .. self.value)
	end
end

function Immediate:encode ()
	local d
	
	return d
end

-- Package object -------------------------------------------------------------

package = {
	parts = {},
	relocations = {}
}

function package:print ()
	local i, v, j, part, field
	
	for i, v in self do
		print (i, v)
	end
	
	print (self.name.data)
	print (self.copyright.data)
	
	for i, part in self.parts do
		for j, field in part do
			print (j, field)
		end
	end

	for i, v in self.relocations do
		print (i, v)
	end
end

-- Package reader object ------------------------------------------------------

packageReader = {
	offset = 1,
	data = ""
}

function packageReader:readByte ()
	local l
	
	l = string.byte (self.data, self.offset)
	self.offset = self.offset + 1
	return l
end

function packageReader:readULong ()
	local l
	
	l = ((string.byte (self.data, self.offset) * 256 +
		string.byte (self.data, self.offset + 1)) * 256 +
		string.byte (self.data, self.offset + 2)) * 256 +
		string.byte (self.data, self.offset + 3)
	self.offset = self.offset + 4
	return l
end

function packageReader:readUShort ()
	local l
	
	l = string.byte (self.data, self.offset) * 256 +
		string.byte (self.data, self.offset + 1)
	self.offset = self.offset + 2
	return l
end

function packageReader:readInfoRef ()
	local i
	
	i = {
		offset = string.byte (self.data, self.offset) * 256 +
			string.byte (self.data, self.offset + 1),
		length = string.byte (self.data, self.offset + 2) * 256 +
			string.byte (self.data, self.offset + 3)
	}
	self.offset = self.offset + 4
	return i
end

function packageReader:readUnicodeString (offset, length)
	local d
	
	d = ""
	for i = 1, length, 2 do
		d = d .. string.char (string.byte (self.data, offset + i))
	end
	return d
end

function packageReader:resolveInfoRef (ref, dataOffset)
	ref.offset = ref.offset + dataOffset;
	ref.data = self:readUnicodeString (ref.offset, ref.length)
end

function packageReader:setFlags ()
	if bit.band (package.flags, bit.lshift (1, 31)) ~= 0
	then package.kAutoRemoveFlag = 1 end
	
	if bit.band (package.flags, bit.lshift (1, 30)) ~= 0
	then package.kCopyProtectFlag = 1 end
	
	if bit.band (package.flags, bit.lshift (1, 28)) ~= 0
	then package.kNoCompressionFlag = 1 end
	
	if bit.band (package.flags, bit.lshift (1, 26)) ~= 0
	then package.kRelocationFlag = 1 end
	
	if bit.band (package.flags, bit.lshift (1, 25)) ~= 0
	then package.kUseFasterCompressionFlag = 1 end
end

function packageReader:readPart (i)
	local part
	
	part = {}
	part.offset = self:readULong ()
	part.size = self:readULong ()
	self:readULong ()
	part.type = self:readULong ()
	self:readULong ()
	part.flags = self:readULong ()
	part.info = self:readInfoRef ()
	self:readULong ()

	table.insert (package.parts, part)
end

function packageReader:readRelocations ()
	local i, j, n, size, pageSize, baseAddr, page, count

	self.offset = package.directorySize + 1	
	self:readULong ()
	size = self:readULong ()
	pageSize = self:readULong ()
	n = self:readULong ()
	baseAddr = 	self:readULong ()
	
	for i = 1, n do
		page = self:readUShort ()
		count = self:readUShort ()
		for j = 1, count do
			table.insert (package.relocations,
				page * pageSize +
				self:readByte () * 4)
		end
	end
	package.startOfFirstPart = package.directorySize + size + 1
end

function packageReader:readPackage (fileName)
	local file, i
	
	file = io.open (fileName)
	self.data = file:read ("*a")
	file:close ()
	
	self.offset = 1 + 8
	self:readULong ()
	package.flags = self:readULong ()
	package.version = self:readULong ()
	package.copyright = self:readInfoRef ()
	package.name = self:readInfoRef ()
	package.size = self:readULong ()
	package.date  = self:readULong ()
	self:readULong ()
	self:readULong ()
	package.directorySize = self:readULong ()
	package.numParts  = self:readULong ()
	
	package.startOfVariableData = self.offset + package.numParts * 4 * 8;
	self:setFlags ()
	self:resolveInfoRef (package.name, package.startOfVariableData)
	self:resolveInfoRef (package.copyright, package.startOfVariableData)
	
	for i = 1, package.numParts do
		self:readPart (i)
	end
	if package.kRelocationFlag then self:readRelocations () end

	return package	
end

-- Part reader ----------------------------------------------------------------

partReader = {
	offset = 1,
	data = ""
}

function partReader:refAsString (ref)
	local r
	if ref.type == "int" or ref.type == "immediate" or ref.type == "char" then
		r = tostring (ref.value)
	elseif ref.type == "magic" then
		r = "@" .. tostring (ref.value)
	else
		r = "#" .. tostring (ref.value)
	end
	return r
end

function partReader:readRef ()
	local type, r
	
	type = bit.band (string.byte (self.data, self.offset + 3), 3)
	if type == 0 then r = self:readIntegerRef ()
	elseif type == 1 then r = self:readPointerRef ()
	elseif type == 2 then
		if bit.band (string.byte (self.data, self.offset + 3), 12) == 8
		then r = self:readCharacterRef ()
		else r = self:readImmediateRef ()
		end
	elseif type == 3 then r = self:readMagicPointerRef ()
	end
	self.offset = self.offset + 4
	return r
end

function partReader:readIntegerRef ()
	local i
	
	i =  ((string.byte (self.data, self.offset) * 256 +
		string.byte (self.data, self.offset + 1)) * 256 +
		string.byte (self.data, self.offset + 2)) * 256 +
		string.byte (self.data, self.offset + 3)
	i = bit.rshift (i, 2)
	return Integer:new (i)
end

function partReader:readPointerRef ()
	local i
	
	i = ((string.byte (self.data, self.offset) * 256 +
		string.byte (self.data, self.offset + 1)) * 256 +
		string.byte (self.data, self.offset + 2)) * 256 +
		string.byte (self.data, self.offset + 3)
	i = i - 1
	return Pointer:new (i)
end

function partReader:readCharacterRef ()
	local i
	
	i = (string.byte (self.data, self.offset + 1) * 256 +
		string.byte (self.data, self.offset + 2)) * 256 +
		string.byte (self.data, self.offset + 3)
	i = bit.rshift (i, 4)
	return Character:new (i)
end

function partReader:readImmediateRef ()
	local r
	
	if string.byte (self.data, self.offset + 3) == 2 then
		r = Immediate:new (nil)
	elseif string.byte (self.data, self.offset + 3) == 18 then
		r = Immediate:new (true)
	else
		r = Symbol:new ("")
	end

	return r
end

function partReader:readMagicPointerRef ()
	local i
	
	i = ((string.byte (self.data, self.offset) * 256 +
		string.byte (self.data, self.offset + 1)) * 256 +
		string.byte (self.data, self.offset + 2)) * 256 +
		string.byte (self.data, self.offset + 3)
	i = bit.rshift (i, 2)
	return MagicPointer:new (i)
end

function partReader:readObject ()
	local type, size, r, padding
	
	if not self.visited[self.offset] then
		size = (string.byte (self.data, self.offset) * 256 +
			string.byte (self.data, self.offset + 1)) * 256 +
			string.byte (self.data, self.offset + 2)
		
		if not self.paddingValue then
			if string.byte (self.data, self.offset + 7) == 1
			then self.paddingValue = 4
			else self.paddingValue = 8
			end
		end
	
		padding = self.paddingValue - math.mod (self.offset + size - 1, self.paddingValue)
		if padding == self.paddingValue then padding = 0 end
		
		type = bit.band (string.byte (self.data, self.offset + 3), 3)
		
		if type == 0 then r = self:readBinaryObject (size)
		elseif type == 1 then r = self:readArrayObject (size)
		elseif type == 3 then r = self:readFrameObject (size)
		end
	end
	return r
end

function partReader:readBinaryObject (size)
	local r, offset, i, n, class
	
	self.offset = self.offset + 8
	n = (size - 12) / 4
	class = self:readRef ()
	if typeof (class) == Pointer then
		offset = self.offset
		self.offset = class.value + 1
		class = self:readObject ()
		self.offset = offset
		r = Binary:new (string.sub (self.data, self.offset + 4,
			self.offset + size - 4), class)
	elseif typeof (class) == Symbol then
		r = Symbol:new (string.sub (self.data, self.offset + 4, self.offset + size - 13))
	end
	
	return r
end

function partReader:readArrayObject (size)
	local r, offset, i, n, ref, class, array

	self.offset = self.offset + 8
	n = (size - 12) / 4
	
	ref = self:readRef ()
	if typeof (ref) == Pointer then
		offset = self.offset
		self.offset = ref.value + 1
		class = self:readObject ()
		self.offset = offset
	end
	
	array = {}
	for i = 1, n do
		ref = self:readRef ()
		if typeof (ref) == Pointer then
			offset = self.offset
			self.offset = ref.value + 1
			table.insert (array, self:readObject ())
			self.offset = offset
		else
			table.insert (array, ref)
		end
	end

	return Array:new (array)
end

function partReader:readFrameObject (size)
	local r, offset, i, n, ref, map, o, frame

	frame = {}
	self.offset = self.offset + 8
	n = (size - 12) / 4

	ref = self:readRef ()
	offset = self.offset
	self.offset = ref.value + 1
	map = self:readObject ()
	self.offset = offset

	for i = 1, n do
		ref = self:readRef ()
		if typeof (ref) == Pointer then
			offset = self.offset
			self.offset = ref.value + 1
			o = self:readObject ()
			rawset (frame, map[i + 1].value, o)
			self.offset = offset
		end
	end

	return Frame:new (frame)
end

function partReader:readPart (data, offset, size)
	local r
	
	self.data = data
	self.offset = offset
	self.size = size
	self.visited = {}
	self.paddingValue = nil
	self.indent = 0
	r = self:readObject ()
	return r
end

-- Main -----------------------------------------------------------------------

print ("-----------------------------------------------------------------------");

fileName = "Open DateMan.pkg"

packageReader:readPackage (fileName)
package:print ()
part = partReader:readPart (
	packageReader.data,
	package.parts[1].offset + package.startOfFirstPart,
	package.parts[1].size)

part:print (0)
