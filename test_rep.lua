#!/usr/bin/env lua

-- Make it easier to test
local src_dir, build_dir = ...
if ( src_dir ) then
    package.path  = src_dir .. "?.lua;" .. package.path
    package.cpath = build_dir .. "?.so;" .. package.cpath
end

require"git2"
require"utils"

print("dump git2 interface")
print(dbg_dump(git2))

local rep = assert(git2.Repository.open("./test_rep/.git"))


print("finished")

