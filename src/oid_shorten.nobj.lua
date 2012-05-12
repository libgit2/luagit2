-- Copyright (c) 2012 by Robert G. Jakabosky <bobby@sharedrealm.com>
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

object "OID_Shorten" {
	c_source [[
typedef git_oid_shorten OID_Shorten;
]],
	constructor "new" {
		c_call "OID_Shorten *" "git_oid_shorten_new" { "size_t", "min_length" },
	},
	destructor {
		c_method_call "void"  "git_oid_shorten_free" {}
	},
	method "add" {
		c_method_call { "GitError", "rc"} "git_oid_shorten_add" { "const char *", "text_oid" },
		c_source[[
		if(${rc} >= 0) {
			lua_pushinteger(L, ${rc});
			return 1;
		}
		]]
	},
}

