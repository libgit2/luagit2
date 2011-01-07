#!/usr/bin/env lua

local build_dir = arg[1]
local git_path = arg[2] or "./test_rep/.git"
-- Make it easier to test
if ( build_dir ) then
    package.cpath = build_dir .. "?.so;" .. package.cpath
end

require"git2"
require"utils"

local function dump_rawobj(obj)
	print('dump RawObject:', obj)
	if obj == nil then
		return
	end
	print('hash = ', obj:hash())
	print('data = "' .. tostring(obj:data()) .. '"')
	print('len = ', obj:len())
	print('type = ', obj:type())
end

-- create database
local db = assert(git2.Database.new())
print("dump Database interface")
print(dbg_dump(db))

-- create backend
local obj_cache = {}
local function get_obj(oid)
	print("------------------- exists callback:", oid)
	if not oid then
		return nil
	end
	-- convert oid to string.
	oid = tostring(oid)
	return obj_cache[oid]
end
local cbs = {
on_read = function(oid)
	local raw_obj = nil
	print("------------------- read callback:", oid)
	raw_obj = get_obj(oid)
	if not raw_obj then
		return nil, git2.GIT.ENOTFOUND
	end
	return raw_obj, git2.GIT.SUCCESS
end,
on_read_header = function(oid)
	local raw_obj = nil
	print("------------------- read_header callback:", oid)
	raw_obj = get_obj(oid)
	if not raw_obj then
		return nil, git2.GIT.ENOTFOUND
	end
	return raw_obj, git2.GIT.SUCCESS
end,
on_write = function(raw_obj)
	local oid = raw_obj:hash()
	print("------------------- write callback:", raw_obj)
	if not oid then
		return nil, -1
	end
	-- convert oid to string.
	local oid_str = tostring(oid)
	-- put raw object in cache
	obj_cache[oid_str] = raw_obj
	return oid, git2.GIT.SUCCESS
end,
on_exists = function(oid)
	local raw_obj = nil
	print("------------------- exists callback:", oid)
	raw_obj = get_obj(oid)
	if not raw_obj then
		return raw_obj, git2.GIT.ENOTFOUND
	end
	return git2.GIT.SUCCESS
end,
on_free = function()
	print("------------------- free callback:")
end,
}

local backend = git2.DatabaseBackend(cbs, 1)

print('add backend:', assert(db:add_backend(backend)))

print('create test blob:')
local raw_obj = git2.RawObject('blob',"any ol content will do")

print("test writing RawObject to database:")
local oid, err = db:write(raw_obj)
print('write:', oid, err)

print()
print("test reading RawObjects from database:")
local object_ids = {
	{'tree', "31f3d5703ce27f0b63c3eb0d829abdc95b51deae"},
	{'commit', "d5a93c463d4cca0068750eb6af7b4b54eea8599b"},
	{'blob', "f534deb63f967cddd4bd440d05d3f6f075e55fca"},
	{'blob', "275a4019807c7bb7bc80c0ca8903bf84345e1bdf"},
}
for _,obj in ipairs(object_ids) do
	local oid = git2.OID.str(obj[2])
	local raw_obj, err = db:read(oid)
	print('read', raw_obj, err)
	dump_rawobj(raw_obj)
	print()
end

db = nil
backend = nil

collectgarbage"collect"
collectgarbage"collect"
collectgarbage"collect"


print()
print()
print("finished")

