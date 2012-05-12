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

object "IndexEntryUnmerged" {
	c_source [[
typedef git_index_entry_unmerged IndexEntryUnmerged;
]],
	method "mode" {
		var_in{"int", "idx"},
		var_out{"unsigned int", "mode"},
		c_source [[
	if(${idx} < 0 || ${idx} >=3) {
		return luaL_argerror(L, ${idx::idx}, "Index out-of-bounds (0-2)");
	}
	${mode} = ${this}->mode[${idx}];
]]
	},
	method "oid" {
		var_in{"int", "idx"},
		var_out{"OID", "oid"},
		c_source [[
	if(${idx} < 0 || ${idx} >=3) {
		return luaL_argerror(L, ${idx::idx}, "Index out-of-bounds (0-2)");
	}
	${oid} = ${this}->oid[${idx}];
]]
	},
	method "path" {
		var_out{"const char *", "ret"},
		c_source "${ret} = ${this}->path;"
	},
}

