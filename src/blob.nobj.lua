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

object "Blob" {
	c_source [[
typedef git_blob Blob;
]],
	extends "Object",
	constructor "new" {
		c_call { "GitError", "err" } "git_blob_new" { "Blob *", "&this", "Repository *", "repo" },
	},
	constructor "lookup" {
		c_call { "GitError", "err" } "git_blob_lookup"
			{ "Blob *", "&this", "Repository *", "repo", "OID", "&id" },
	},
	c_function "writefile" {
		c_call { "GitError", "err>2" } "git_blob_writefile"
			{ "OID", "&written_id>1", "Repository *", "repo", "const char *", "path" },
	},
	method "set_rawcontent_fromfile" {
		c_method_call { "GitError", "err" } "git_blob_set_rawcontent_fromfile"
			{ "const char *", "filename" }
	},
	method "set_rawcontent" {
		c_method_call { "GitError", "err" } "git_blob_set_rawcontent"
			{ "const char *", "buffer", "size_t", "#buffer" }
	},
	method "rawcontent" {
		var_out{"const char *", "buffer", has_length = true},
		c_source [[
	${buffer} = git_blob_rawcontent(${this});
	${buffer_len} = git_blob_rawsize(${this});
]]
	},
	method "rawsize" {
		c_method_call "int"  "git_blob_rawsize" {}
	},
}

