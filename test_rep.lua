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

local oid = git2.OID.str("d5a93c463d4cca0068750eb6af7b4b54eea8599b")
print("dump OID interface")
print(dbg_dump(oid))
print('convert OID value to string = <' .. tostring(oid) .. '>')

print('test writing to the object database:')
local raw_obj = git2.RawObject.new('blob',"any ol content will do")
print()
print("dump RawObject interface")
print(dbg_dump(raw_obj))
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
print()
print("dump RawObject info:")
dump_rawobj(raw_obj)

print()
print("test closing of RawObject:")
raw_obj:close()
dump_rawobj(raw_obj)

print()
print("test setting data of RawObject:")
raw_obj:set_data("any ol content will do")
dump_rawobj(raw_obj)

local db = rep:database()
print("dump Database interface")
print(dbg_dump(db))

print()
print("test writing RawObject to database:")
local oid, err = db:write(raw_obj)
print(oid, err)

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
	print()
	print(raw_obj, err)
	dump_rawobj(raw_obj)
end


local commit_id = git2.OID.str("d5a93c463d4cca0068750eb6af7b4b54eea8599b")
print()
print("test parsing a commit object: ", commit_id)
local commit2, err = rep:lookup(commit_id, 'commit')
print(commit2, err)
local commit1, err = git2.Commit.lookup(rep, commit_id)
print(commit1, err)
assert(commit1 == commit2)
print("dump Commit interface")
print(dbg_dump(commit1))
local function dump_signature(pre, sig)
	print(pre .. '.name = ', sig:name())
	print(pre .. '.email = ', sig:email())
	print(pre .. '.when = ', sig:when())
end
local function dump_blob(blob)
	print("dump Blob interface")
	print(dbg_dump(blob))
	print('blob.rawcontent.size =', blob:rawsize())
	print('blob.rawcontents =', blob:rawcontent())
end
local function dump_tree_entry(entry)
	if entry == nil then
		return
	end
	print('tree_entry.id = ', entry:id())
	print('tree_entry.name = ', entry:name())
	print('tree_entry.attributes = ', string.format('0x%08X', entry:attributes()))
	local obj = entry:object()
	print('tree_entry.object = ', obj)
	if obj:type() == 'blob' then
		dump_blob(obj)
	end
end
local function dump_tree(tree)
	if tree == nil then
		return
	end
	print('id = ', tree:id())
	local cnt = tree:entrycount()
	print('entrycount = ', cnt)
	for i=0,cnt-1 do
		local entry = tree:entry_byindex(i)
		print('entry:', entry)
		dump_tree_entry(entry)
	end
end
local function dump_commit(commit)
	if commit == nil then
		return
	end
	print('message = ', commit:message())
	print('message_short = ', commit:message_short())
	print('time = ', commit:time())
	print('tree = ', commit:tree())
	dump_tree(commit:tree())
	dump_signature('committer', commit:committer())
	dump_signature('author', commit:author())
	local cnt = commit:parentcount()
	print('parentcount = ', cnt)
	for i=0,cnt-1 do
		local parent = commit:parent(i)
		print('parent:', parent)
		dump_commit(parent)
	end
end
dump_commit(commit1)

local index = rep:index()
print("dump Index interface")
print(dbg_dump(index))
local function dump_index_entry(entry)
	if entry == nil then
		return
	end
	print(' idx.entry.ctime = ', entry:ctime())
	print(' idx.entry.mtime = ', entry:mtime())
	print(' idx.entry.dev = ', entry:dev())
	print(' idx.entry.ino = ', entry:ino())
	print(' idx.entry.mode = ', entry:mode())
	print(' idx.entry.uid = ', entry:uid())
	print(' idx.entry.gid = ', entry:gid())
	print(' idx.entry.file_size = ', entry:file_size())
	print(' idx.entry.id = ', entry:id())
	print(' idx.entry.flags = ', string.format('0x%08X', entry:flags()))
	print(' idx.entry.flags_extended = ', string.format('0x%08X', entry:flags_extended()))
	print(' idx.entry.path = ', entry:path())
end
local function dump_index(index)
	if index == nil then
		return
	end
	local cnt = index:entrycount()
	print('entrycount = ', cnt)
	for i=0,cnt-1 do
		local entry = index:get(i)
		print('entry:', entry)
		dump_index_entry(entry)
	end
end
print('index:read():', index:read())
dump_index(index)

local revwalk = git2.RevWalk(rep)
print("dump RevWalk interface")
print(dbg_dump(revwalk))
print('sorting:', revwalk:sorting(revwalk.SORT_TOPOLOGICAL + revwalk.SORT_REVERSE))
local head_id = git2.OID.str("5c697d74eb692d650799ca1b0a10254d7130953d")
local head = assert(git2.Commit.lookup(rep, head_id))
print('push:', revwalk:push(head))
assert(revwalk:repository() == rep)

local commit = revwalk:next()
while (commit ~= nil) do
	dump_commit(commit)
	-- get next commit
	commit = revwalk:next()
end

local tag_id = git2.OID.str('82dfe36284d77b608ccc9d96e0ffa5782cb7c835')
local tag = git2.Tag.lookup(rep, tag_id)
print("dump Tag interface")
print(dbg_dump(tag))
local function dump_tag(tag)
	if tag == nil then
		return
	end
	print('name = ', tag:name())
	dump_signature('tagger', tag:tagger())
	print('message = ', tag:message())
	local obj = tag:target()
	print('target = ', obj)
end
dump_tag(tag)


revwalk = nil
head = nil
commit = nil
commit1 = nil
commit2 = nil
index = nil
rep = nil
db = nil

collectgarbage"collect"
collectgarbage"collect"
collectgarbage"collect"


print()
print()
print("finished")

