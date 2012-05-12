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

object "StrArray" {
	userdata_type = "embed",
	c_source [[
typedef git_strarray StrArray;
]],
	constructor "new" {
		c_source[[
	StrArray array;
	array.strings = NULL;
	array.count = 0;
	${this} = &array;
]]
	},
	destructor "free" {
		c_source[[
	if(${this}->strings != 0) {
		git_strarray_free(${this});
		${this}->strings = NULL;
	}
]]
	},
	field "size_t" "count" { "ro" },
	method "str" {
		var_in{ "size_t", "n" },
		var_out{ "const char *", "str" },
		c_source[[
	if(${n} < ${this}->count) {
		${str} = ${this}->strings[${n}];
	}
]],
	},
	method "get_array" {
		var_out{ "<any>", "array" },
		c_source "pre" [[
	size_t n;
]],
		c_source[[
	lua_createtable(L, ${this}->count, 0);
	for(n = 0; n < ${this}->count; n++) {
		lua_pushstring(L, ${this}->strings[n]);
		lua_rawseti(L, -2, n+1);
	}
]]
	}
}

