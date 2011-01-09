-- Copyright (c) 2010 by Robert G. Jakabosky <bobby@sharedrealm.com>
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

function dump_meta_recur(seen, obj, depth, dbg)
	local meta = getmetatable(obj)
	if meta == nil then return '' end
	local out = ', mt: ' .. tostring(meta) .. ' '
	-- check if this metatable has been seen already.
	if seen[meta] then 
		return out .. tostring(meta)
	end
	return out .. dump_recur(seen, meta, depth, dbg)
end

function dump_recur(seen, obj, depth, dbg)
	local t = type(obj)
	-- if not a table just convert to string.
	if t ~= "table" then
		local out
		if t == "string" then
			out = '"' .. obj .. '"'
		else
			out = tostring(obj)
			if dbg == 1 then
				out = out .. dump_meta_recur(seen, obj, depth, dbg) 
			end
		end
		return out
	end
	-- check if table has a __tostring metamethod.
	if dbg ~= 1 then
		local m = getmetatable(obj)
		if m then
			local tostr = m.__tostring
			if tostr then
				out = '"' .. tostr(obj) .. '"'
				return out
			end
		end
	end
	-- check if this table has been seen already.
	if seen[obj] then 
		return "Already dumped " .. tostring(obj)
	end
	seen[obj] = true
	-- restrict max depth.
	if depth >= 10 then
		return "{... max depth reached ...}"
	end
	depth = depth + 1
	-- output table key/value pairs
	local tabs = string.rep("  ",depth)
	local out
	if dbg == 1 then
		out = tostring(obj) .. " {\n"
	else
		out = "{\n"
	end
	for k,v in pairs(obj) do
		if type(k) ~= "number" then
			out = out .. tabs .. '[' .. dump_recur(seen, k, depth, dbg) .. '] = ' ..
				dump_recur(seen, v, depth, dbg) .. ',\n'
		else
			out = out .. tabs .. '[' .. k .. '] = ' .. dump_recur(seen, v, depth, dbg) .. ',\n'
		end
	end
	out = out .. tabs:sub(1,-3) .. "}"
	if dbg == 1 then
		out = out .. dump_meta_recur(seen, obj, depth, dbg)
	end
	return out
end

function dbg_dump(obj)
	local seen = {}
	return dump_recur(seen, obj, 0, 1)
end

function dump(obj)
	local seen = {}
	return dump_recur(seen, obj, 0, 0)
end

local function sizeof2(size, test, ...)
	collectgarbage"collect"
	size= collectgarbage"count"*1024 - size
	print("used size: " .. size)
	return size, ...
end

function sizeof(test, ...)
	local size=0
	if type(test) == "string" then
		test=assert(loadstring(test))
	end
	collectgarbage"collect"
	size=collectgarbage"count"*1024
	return sizeof2(size, test, test(...))
end

