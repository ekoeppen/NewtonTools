#!/usr/local/bin/luacheia5

cheia.load "pack"
cheia.load "bit"

-- Constants -------------------------------------------------------------------

Frame = {_type = "Frame"}
Array = {_type = "Array"}
Symbol = {_type = "Symbol"}
Binary = {_type = "Binary"}
Integer = {_type = "Integer"}
String = {_type = "String"}

kImmediate = 0
kCharacter = 1
kUnicodeCharacter = 2
kBinaryObject = 3
kArray = 4
kPlainArray = 5
kFrame = 6
kSymbol = 7
kString = 8
kPrecedent = 9
kNIL = 10
kSmallRect = 11
kLargeBinary = 12

precedents = {}
precedentSymbols = {}
lastPrecedent = 0

-- Utility functions -----------------------------------------------------------

function xlong (n)
	local d
	
	if n < 255
	then
		d = string.char (n)
	else
		d = string.char (255) ..
			string.char (bit.band (bit.rshift (n, 24), 255)) ..
			string.char (bit.band (bit.rshift (n, 16), 255)) ..
			string.char (bit.band (bit.rshift (n, 8), 255)) ..
			string.char (bit.band (n, 255))
	end
	return d
end

function addPrecedentSymbol (s)
	if getPrecedentSymbol (s) == nil then
		rawset (precedentSymbols, s, lastPrecedent)
		lastPrecedent = lastPrecedent + 1
	end
end

function addPrecedent (o)
end

function getPrecedentSymbol (s)
	return rawget (precedentSymbols, s)
end

function getPrecedent (o)
end

-- Frame -----------------------------------------------------------------------

function Frame:new (f)
	f = f or {}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Frame:tostring ()
	local d, i, v, s
	
	d = "{"
	s = ""
	for i, v in pairs (self) do
		d = d .. s .. i .. ": " .. v:tostring()
		s = ", "
	end
	print (d)
	return d
end

function Frame:print (indent)
	local i, v, s
	
	print (string.rep (" ", indent * 4) .. "{")
	s = ""
	for i, v in pairs (self) do
		io.write (string.rep (" ", indent * 4) .. i)
		print (":")
		v:print (indent + 1)
	end
	print (string.rep (" ", indent * 4) .. "}")
end

function Frame:encode ()
	local i, v, d
	
	d = string.char (kFrame) .. xlong (self:size (self))
	for i in pairs (self) do
		addPrecedentSymbol (i)
		d = d .. string.char (kSymbol) ..
			string.char (string.len (i)) .. i
	end
	for i, v in pairs (self) do
		d = d .. v:encode ()
	end
	return d
end

function Frame:size ()
	local i, n
	
	n = 0
	for i in pairs (self) do n = n + 1 end
	return n
end

-- Array -----------------------------------------------------------------------

function Array:new (f)
	f = f or {}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Array:tostring ()
	local d, s
	
	d = "["
	s = ""
	for i, v in ipairs (self) do
		d = d .. s .. v:tostring()
		s = ", "
	end
	d = d .. "]"
	return d
end

function Array:print (indent)
	local s
	
	print (string.rep (" ", indent * 4) .. "[")
	for i, v in ipairs (self) do
		v:print (indent + 1)
	end
	print (string.rep (" ", indent * 4) .. "]")
end

function Array:encode ()
	local i, v, d
	
	d = string.char (kPlainArray) .. xlong (table.getn (self))
	for i, v in ipairs (self) do
		d = d .. v:encode ()
	end
	return d
end

-- String ----------------------------------------------------------------------

function String:new (s)
	local f
	f = {value = s}
	setmetatable (f, self)
	self.__index = self
	return f
end

function String:tostring ()
	return "\"" .. self.value .. "\""
end

function String:print (indent)
	print (string.rep (" ", indent * 4) .. "\"" .. self.value .. "\"")
end

function String:encode ()
	local d, i, v
	
	d = string.char (kString) .. xlong (string.len (self.value) * 2 + 2)
	for i = 1, string.len (self.value) do
		d = d .. string.char (0) .. string.char (string.byte (self.value, i))
	end
	d = d .. string.char (0) .. string.char (0)
	return d
end

-- Symbol ----------------------------------------------------------------------

function Symbol:new (s)
	local f
	f = {value = s}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Symbol:tostring ()
	return "'" .. self.value
end

function Symbol:print (indent)
	print (string.rep (" ", indent * 4) .. self.value)
end

function Symbol:encode ()
	local p, d
	
	p = getPrecedentSymbol (self.value)
	if p == nil then
		addPrecedentSymbol (self.value)
		d = string.char (kSymbol) ..
			xlong (string.len (self.value)) .. self.value
	else
		d = string.char (kPrecedent) .. xlong (p)
	end
	return d
end

-- Integer ---------------------------------------------------------------------

function Integer:new (s)
	local f
	f = {value = s}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Integer:tostring ()
	return i
end

function Integer:print (indent)
	print (string.rep (" ", indent * 4) .. self.value)
end

function Integer:encode ()
	return string.char (kImmediate) .. xlong (bit.lshift (self.value, 2))
end

-- Binary ----------------------------------------------------------------------

function Binary:new (s, c)
	local f
	f = {value = s, class = Symbol:new (c)}
	setmetatable (f, self)
	self.__index = self
	return f
end

function Binary:tostring ()
	return "{<" .. self.class:tostring () .. ">, length: " .. string.len (self.value) .. "}"
end

function Binary:print (indent)
	if nil then
		print (string.rep (" ", indent * 4) ..
			"{<" .. self.class.value .. 
			">, length: " .. string.len (self.value) .. "}")
	else
		print (string.rep (" ", indent * 4) ..
			"{<binary>, length: " .. string.len (self.value) .. "}")
	end
end

function Binary:encode ()
	return string.char (kBinaryObject) ..
		xlong (string.len (self.value)) ..
		self.class:encode () ..
		self.value
end

