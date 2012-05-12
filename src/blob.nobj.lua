-- Copyright (c) 2010-2012 by Robert G. Jakabosky <bobby@sharedrealm.com>
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
	constructor "lookup" {
		c_call { "GitError", "err" } "git_blob_lookup"
			{ "Blob *", "&this", "Repository *", "repo", "OID", "&id" },
	},
	c_function "fromfile" {
		c_call { "GitError", "err>2" } "git_blob_create_fromfile"
			{ "OID", "&written_id>1", "Repository *", "repo", "const char *", "path" },
	},
	c_function "frombuffer" {
		c_call { "GitError", "err" } "git_blob_create_frombuffer"
			{ "OID", "&written_id>1", "Repository *", "repo",
				"const char *", "buffer", "size_t", "#buffer" },
	},
	method "rawcontent" {
		c_method_call { "const char *", "buff" } "git_blob_rawcontent" {},
		c_method_call { "size_t", "#buff" } "git_blob_rawsize" {},
	},
	method "rawsize" {
		c_method_call "int"  "git_blob_rawsize" {}
	},
}

