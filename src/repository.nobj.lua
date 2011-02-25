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

object "Repository" {
	c_source [[
typedef git_repository Repository;
]],
	constructor "open" {
		c_call { "GitError", "err" } "git_repository_open"
			{ "Repository *", "&this>1", "const char *", "path" },
	},
	constructor "open2" {
		c_call { "GitError", "err" } "git_repository_open2"
			{ "Repository *", "&this>1", "const char *", "dir", "const char *", "object_directory",
				"const char *", "index_file", "const char *", "work_tree" },
	},
	constructor "open3" {
		c_call { "GitError", "err" } "git_repository_open3"
			{ "Repository *", "&this>1", "const char *", "dir", "Database *", "object_database",
				"const char *", "index_file", "const char *", "work_tree" },
	},
	constructor "init" {
		c_call { "GitError", "err" } "git_repository_init"
			{ "Repository *", "&this>1", "const char *", "path", "unsigned int", "is_bare" },
	},
	destructor {
		c_method_call "void"  "git_repository_free" {}
	},
	method "database" {
		c_method_call "Database *" "git_repository_database" {}
	},
	method "index" {
		c_call { "GitError", "err" } "git_repository_index"
			{ "Index *", "&index>1", "Repository *", "this" },
	},
	method "lookup" {
		c_call { "int", "(otype)" } "git_object_string2type" { "const char *", "type<3" },
		c_call { "GitError", "err" } "git_repository_lookup"
			{ "Object *", "&obj>1", "Repository *", "this<1", "OID", "&id<2", "int", "otype" },
	},
	method "newobject" {
		c_call { "int", "(otype)" } "git_object_string2type" { "const char *", "type<2" },
		c_call { "GitError", "err" } "git_repository_newobject"
			{ "Object *", "&obj>1", "Repository *", "this<1", "int", "otype" },
	},
	method "blob_writefile" {
		c_call { "GitError", "err" } "git_blob_writefile"
			{ "OID", "&written_id>1", "Repository *", "this<1", "const char *", "path" },
	},
}

