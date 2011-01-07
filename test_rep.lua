#!/usr/bin/env lua

local build_dir = arg[1]
local git_path = arg[2] or "./test_rep/.git"
-- Make it easier to test
if ( build_dir ) then
    package.cpath = build_dir .. "?.so;" .. package.cpath
end

require"git2"
require"utils"

print("dump git2 interface")
print(dbg_dump(git2))

local rep = assert(git2.Repository.open(git_path))

print("dump Repository interface")
print(dbg_dump(rep))

local db = rep:database()
print("dump Database interface")
print(dbg_dump(db))

local index = rep:index()
print("dump Index interface")
print(dbg_dump(index))

local oid = git2.OID.str("d5a93c463d4cca0068750eb6af7b4b54eea8599b")
print("dump OID interface")
print(dbg_dump(oid))
print('convert OID value to string = <' .. tostring(oid) .. '>')

print('test writing to the object database:')
local raw_obj = git2.RawObject(git2.OType('blob'),"any ol content will do")
print("dump RawObject interface")
print(dbg_dump(raw_obj))
print("dump RawObject info:")
print('hash = ', raw_obj:hash())
print('data = "' .. tostring(raw_obj:data()) .. '"')
print('len = ', raw_obj:len())
print('type = ', raw_obj:type())
print("test closing of RawObject:")
raw_obj:close()
print('hash = ', raw_obj:hash())
print('data = "' .. tostring(raw_obj:data()) .. '"')
print('len = ', raw_obj:len())
print('type = ', raw_obj:type())


print("finished")

