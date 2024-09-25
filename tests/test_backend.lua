#!/usr/bin/env lua

local build_dir = arg[1]
local git_path = arg[2] or "./tests/test_rep/.git/"
-- Make it easier to test
if ( build_dir ) then
    package.cpath = build_dir .. "?.so;" .. package.cpath
end

local git2 = require"git2"
require"utils"

--print(dump(git2))
local function dump_obj(obj)
	print('dump OdbObject:', obj)
	if obj == nil then
		return
	end
	print('id = ', obj:id())
	print('type = ', obj:type())
	local data = obj:data()
	print('data = ', data)
	if data then
		print('hash = ', git2.ODB.hash(data,git2.Object.string2type(obj:type())))
	end
end

-- create odb
local db = assert(git2.ODB.new())
print("=============================================== new db=", db)
print("dump ODB interface")
--print(dbg_dump(db))

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
	print("------------------- read callback:", oid)
	local obj = get_obj(oid)
	if not obj then
		return nil, git2.ENOTFOUND
	end
	return obj.data, obj.otype
end,
on_read_prefix = function(short_oid, len)
	print("------------------- read_prefix callback:", oid)
	local obj = get_obj(short_oid)
	if not obj then
		if len ~= git2.OID.HEXSZ then
			return nil, git2.ENOTIMPLEMENTED
		end
		return nil, git2.ENOTFOUND
	end
	return obj.data, obj.otype, short_oid
end,
on_read_header = function(oid)
	print("------------------- read_header callback:", oid)
	local obj = get_obj(oid)
	if not obj then
		return nil, git2.ENOTFOUND
	end
	return obj.len, obj.otype
end,
on_write = function(oid, data, otype)
	print("------------------- write callback:", oid, data, otype)
	if not oid then
		return nil, -1
	end
	-- convert oid to string.
	local oid_str = tostring(oid)
	-- put raw object in cache
	obj_cache[oid_str] = { data = data, len = #data, otype = otype}
	return oid
end,
on_exists = function(oid)
	print("------------------- exists callback:", oid)
	local obj = get_obj(oid)
	if not obj then
		return false
	end
	return true
end,
on_free = function()
	print("------------------- free callback:")
end,
}

local backend = git2.ODBBackend(cbs)

print('add backend:', assert(db:add_backend(backend, 0)))
backend = nil
collectgarbage"collect"

print("test writing test blob to odb:")
local oid, err = db:write("any ol content will do", 'blob')
print('write:', oid, err)

print()
print("test reading RawObjects from odb:")
local object_ids = {
	{'tree', "31f3d5703ce27f0b63c3eb0d829abdc95b51deae"},
	{'commit', "d5a93c463d4cca0068750eb6af7b4b54eea8599b"},
	{'blob', "f534deb63f967cddd4bd440d05d3f6f075e55fca"},
	{'blob', "275a4019807c7bb7bc80c0ca8903bf84345e1bdf"},
}
for _,obj in ipairs(object_ids) do
	local oid = git2.OID.hex(obj[2])
	local obj, err = db:read(oid)
	print('read', obj, err)
	dump_obj(obj)
	print()
end

print("Creating repository from git repository:", git_path)
local status, rep = pcall(git2.Repository.open_no_backend,
	git_path, git_path .. 'objects', git_path .. 'index', git_path .. '../')

if not status then
	rep = assert(git2.Repository.open(git_path))
else
	print("Created repository with no backends from git repository:", git_path)
end
db = rep:odb()
print("=============================================== repo db=", db)
backend = git2.ODBBackend(cbs)
print("add backend repository's odb:", assert(db:add_backend(backend, 0)))
backend = nil
collectgarbage"collect"

print()
print("try reading objects from repository:")
local object_ids = {
	{'tree', "31f3d5703ce27f0b63c3eb0d829abdc95b51deae"},
	{'commit', "d5a93c463d4cca0068750eb6af7b4b54eea8599b"},
	{'blob', "f534deb63f967cddd4bd440d05d3f6f075e55fca"},
	{'blob', "275a4019807c7bb7bc80c0ca8903bf84345e1bdf"},
}
for _,obj in ipairs(object_ids) do
	local oid = git2.OID.hex(obj[2])
	--local obj, err = rep:lookup(oid, obj[1])
	local obj, err = db:read(oid)
	print('read', obj, err)
	print()
end

db = nil
backend = nil
obj_cache = nil

collectgarbage"collect"
collectgarbage"collect"
collectgarbage"collect"


print()
print()
print("finished")

