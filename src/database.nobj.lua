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

object "Database" {
	c_source [[
typedef git_odb Database;
]],
	constructor "new" {
		c_call {"GitError", "err"} "git_odb_new" { "Database *", "&this" },
	},
	constructor "open" {
		c_call {"GitError", "err"} "git_odb_open"
			{ "Database *", "&this", "const char *", "object_dir" },
	},
	destructor "close" {
		c_method_call "void"  "git_odb_close" {}
	},
	--[=[
	method "add_backend" {
		var_in{"DatabaseBackend *", "backend"},
		var_in{"int", "priority"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_add_backend(${this}, &(${backend}->backend), ${priority});
	DatabaseBackend_ref(${backend});
]],
	},
	method "add_alternate" {
		var_in{"DatabaseBackend *", "backend"},
		var_in{"int", "priority"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_add_alternate(${this}, &(${backend}->backend), ${priority});
	DatabaseBackend_ref(${backend});
]],
	},
	--]=]
	method "read" {
		c_call "GitError" "git_odb_read"
			{ "!OdbObject *", "&out>1", "Database *", "this", "OID", "&id"},
	},
	method "read_header" {
		c_call { "GitError", "err>3" } "git_odb_read_header"
			{ "size_t", "&size>1", "git_otype", "&(otype)", "Database *", "this", "OID", "&id"},
		c_call { "const char *", "type>2" } "git_object_type2string" { "git_otype", "otype" },
	},
	method "write" {
		c_call { "git_otype", "(otype)" } "git_object_string2type" { "const char *", "type<3" },
		c_call "GitError" "git_odb_write"
			{ "OID", "&id>1", "Database *", "this<1", "const char *", "data<2", "size_t", "#data",
			  "git_otype", "otype"},
	},
	method "exists" {
		c_method_call { "GitError", "err" } "git_odb_exists" { "OID", "&id" }
	},
}

