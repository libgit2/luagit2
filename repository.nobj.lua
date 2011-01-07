-- Copyright (c) 2010 by Robert G. Jakabosky <bobby@neoawareness.com>
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

c_source [[
typedef git_repository Repository;
]]

object "Repository" {
	constructor "open" {
		var_in{"const char *", "path"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_repository_open(&(${this}), ${path});
]],
	},
	constructor "open2" {
		var_in{"const char *", "dir"},
		var_in{"const char *", "object_directory"},
		var_in{"const char *", "index_file"},
		var_in{"const char *", "work_tree"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_repository_open2(&(${this}), ${dir}, ${object_directory}, ${index_file}, ${work_tree});
]],
	},
	destructor {
		c_call "void"  "git_repository_free" {}
	},
	method "database" {
		c_call "Database *" "git_repository_database" {}
	},
	method "index" {
		c_call "Index *" "git_repository_index" {}
	},
	method "lookup" {
		var_in{"OID", "id"},
		var_in{"OType", "type"},
		var_out{"Object *", "obj"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_repository_lookup(&(${obj}), ${this}, &(${id}), ${type});
]],
	},
	method "newobject" {
		var_in{"OType", "type"},
		var_out{"Object *", "obj"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_repository_newobject(&(${obj}), ${this}, ${type});
]],
	},
	method "blob_writefile" {
		var_in{"const char *", "path"},
		var_out{"OID", "written_id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_blob_writefile(&(${written_id}), ${this}, ${path});
]],
	},
}

