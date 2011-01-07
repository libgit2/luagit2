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
typedef git_blob Blob;
]]

object "Blob" {
	extends "Object",
	constructor "new" {
		var_in{"Repository *", "repo"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_blob_new(&(${this}), ${repo});
]],
	},
	constructor "lookup" {
		var_in{"Repository *", "repo"},
		var_in{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_blob_lookup(&(${this}), ${repo}, &(${id}));
]],
	},
	c_function "writefile" {
		var_in{"Repository *", "repo"},
		var_in{"const char *", "path"},
		var_out{"OID", "written_id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_blob_writefile(&(${written_id}), ${repo}, ${path});
]],
	},
	method "set_rawcontent_fromfile" {
		c_call "GitError"  "git_blob_set_rawcontent_fromfile" { "const char *", "filename" }
	},
	method "set_rawcontent" {
		var_in{"const char *", "buffer"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_blob_set_rawcontent(${this}, ${buffer}, ${buffer}_len);
]]
	},
	method "rawcontent" {
		var_out{"const char *", "buffer", has_length = true},
		c_source [[
	${buffer} = git_blob_rawcontent(${this});
	${buffer}_len = git_blob_rawsize(${this});
]]
	},
}

