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

object "OID" {
	c_source [[
typedef git_oid OID;
]],
	userdata_type = 'simple',
	constructor "str" {
		c_call {"GitError", "err"} "git_oid_mkstr"
			{ "OID", "&this", "const char *", "hex" },
	},
	constructor "raw" {
		c_call "void" "git_oid_mkraw" { "OID", "&this", "const unsigned char *", "raw" },
	},
	method "__str__" {
		var_out{"const char *", "ret"},
    c_source [[
	char buf[GIT_OID_HEXSZ+1];
  git_oid_fmt(buf, &(${this}));
	buf[GIT_OID_HEXSZ] = 0;
	${ret} = buf;
]],
	},
	method "__eq__" {
		c_call {"int", "ret"} "git_oid_cmp" { "OID", "&this", "OID", "&id" },
	},
}

