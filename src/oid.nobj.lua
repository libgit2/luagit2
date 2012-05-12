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

object "OID" {
	export_definitions {
		RAWSZ         = "GIT_OID_RAWSZ",
		HEXSZ         = "GIT_OID_HEXSZ",
		MINPREFIXLEN  = "GIT_OID_MINPREFIXLEN",
	},
	c_source [[
typedef git_oid OID;
]],
	userdata_type = 'simple',
	constructor "hex" {
		c_call {"GitError", "err"} "git_oid_fromstrn"
			{ "OID", "&this", "const char *", "str", "size_t", "#str" },
	},
	constructor "raw" {
		c_source[[
		if(${raw_len} < GIT_OID_RAWSZ) {
			lua_pushnil(L);
			lua_pushliteral(L, "Invalid RAW OID");
			return 2;
		}
		]],
		c_call "void" "git_oid_fromraw" { "OID", "&this", "const unsigned char *", "raw" },
	},
	method "pathfmt" {
		var_out{"const char *", "ret"},
    c_source [[
	char buf[GIT_OID_HEXSZ+1+1];
  git_oid_pathfmt(buf, &(${this}));
	buf[GIT_OID_HEXSZ] = 0;
	${ret} = buf;
]],
	},
	method "fmt" {
		var_out{"const char *", "ret"},
    c_source [[
	char buf[GIT_OID_HEXSZ+1];
  git_oid_fmt(buf, &(${this}));
	buf[GIT_OID_HEXSZ] = 0;
	${ret} = buf;
]],
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

