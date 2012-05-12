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

object "ODB" {
	c_source [[
typedef git_odb ODB;
]],
	constructor "new" {
		c_call {"GitError", "err"} "git_odb_new" { "ODB *", "&this" },
	},
	constructor "open" {
		c_call {"GitError", "err"} "git_odb_open"
			{ "ODB *", "&this", "const char *", "object_dir" },
	},
	destructor "free" {
		c_method_call "void"  "git_odb_free" {}
	},
	method "add_backend" {
		var_in{"ODBBackend *", "backend"},
		var_in{"int", "priority"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_add_backend(${this}, &(${backend}->backend), ${priority});
	ODBBackend_ref(${backend});
]],
	},
	method "add_alternate" {
		var_in{"ODBBackend *", "backend"},
		var_in{"int", "priority"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_add_alternate(${this}, &(${backend}->backend), ${priority});
	ODBBackend_ref(${backend});
]],
	},
	method "read" {
		c_call "GitError" "git_odb_read"
			{ "!OdbObject *", "&out>1", "ODB *", "this", "OID", "&id"},
	},
	method "read_prefix" {
		c_call "GitError" "git_odb_read_prefix"
			{ "!OdbObject *", "&out>1", "ODB *", "this", "OID", "&short_id", "unsigned int", "len"},
	},
	method "read_header" {
		c_call { "GitError", "err>3" } "git_odb_read_header"
			{ "size_t", "&len_p>1", "git_otype", "&(otype)", "ODB *", "this", "OID", "&id"},
		c_call { "const char *", "type>2" } "git_object_type2string" { "git_otype", "otype" },
	},
	method "exists" {
		c_method_call { "GitError", "err" } "git_odb_exists" { "OID", "&id" }
	},
	method "write" {
		c_call { "git_otype", "(otype)" } "git_object_string2type" { "const char *", "type<3" },
		c_call "GitError" "git_odb_write"
			{ "OID", "&id>1", "ODB *", "this<1", "const char *", "data<2", "size_t", "#data",
			  "git_otype", "otype"},
	},
	c_function "hash" {
		c_call { "GitError", "err" } "git_odb_hash"
			{ "OID", "&id>1", "const char *", "data", "size_t", "#data", "git_otype", "otype"}
	},
	c_function "hashfile" {
		c_call { "GitError", "err" } "git_odb_hashfile"
			{ "OID", "&id>1", "const char *", "path", "git_otype", "otype"}
	},
}

