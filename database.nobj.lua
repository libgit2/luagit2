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

c_source [[
typedef git_odb Database;
]]

object "Database" {
	constructor "new" {
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_new(&(${this}));
]],
	},
	constructor "open" {
		var_in{"const char *", "object_dir"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_open(&(${this}), ${object_dir});
]],
	},
	destructor "close" {
		c_call "void"  "git_odb_close" {}
	},
	method "add_backend" {
		var_in{"DatabaseBackend *", "backend"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_add_backend(${this}, &(${backend}->backend));
	DatabaseBackend_ref(${backend});
]],
	},
	method "read" {
		var_in{"OID", "id"},
		var_out{"RawObject *", "obj"},
		var_out{"GitError", "err"},
		c_source [[
	RawObject raw;
	git_rawobj obj;
	${err} = git_odb_read(&(obj), ${this}, &(${id}));
	if(${err} == GIT_SUCCESS) {
		/* convert git_rawobj to RawObject */
		RawObject_from_git_rawobj(L, &raw, &obj);
		${obj} = &(raw);
	}
]],
	},
	method "read_header" {
		var_in{"OID", "id"},
		var_out{"RawObject *", "obj"},
		var_out{"GitError", "err"},
		c_source [[
	RawObject raw;
	git_rawobj obj;
	${err} = git_odb_read_header(&(obj), ${this}, &(${id}));
	if(${err} == GIT_SUCCESS) {
		/* convert git_rawobj to RawObject */
		RawObject_from_git_rawobj(L, &raw, &obj);
		${obj} = &(raw);
	}
]],
	},
	method "write" {
		var_in{"RawObject *", "obj"},
		var_out{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_write(&(${id}), ${this}, &(${obj}->raw));
]],
	},
	method "exists" {
		var_in{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_odb_exists(${this}, &(${id}));
]],
	},
}

