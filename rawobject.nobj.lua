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
typedef struct RawObject {
	git_rawobj raw;
	int ref;
} RawObject;

static void RawObject_set_data_and_ref(lua_State *L, RawObject *obj, const char *data, int len, int idx) {
	/* clear old data. */
	if(obj->ref == LUA_NOREF) {
		if(obj->raw.data != NULL) {
			git_rawobj_close(&(obj->raw));
		}
	} else {
		/* this raw object was pointing to a Lua string, release our reference to it. */
		luaL_unref(L, LUA_REGISTRYINDEX, obj->ref);
	}
	obj->raw.data = (void *)data;
	obj->raw.len = len;
	if(data) {
		/* keep a reference to the Lua string. */
		lua_pushvalue(L, idx);
		obj->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	} else {
		obj->ref = LUA_NOREF;
	}
}
]]

object "RawObject" {
	userdata_type = 'embed',
	default = 'NULL',
	constructor {
		var_in{"const char *", "type"},
		var_in{"const char *", "data"},
		c_source [[
	RawObject obj;
	${this} = &(obj);
	obj.raw.data = NULL;
	obj.raw.len = 0;
	obj.raw.type = git_object_string2type(${type});
	obj.ref = LUA_NOREF;
	RawObject_set_data_and_ref(L, &obj, ${data}, ${data}_len, ${data::idx});
]],
	},
	destructor "close" {
		c_source [[
	RawObject_set_data_and_ref(L, ${this}, NULL, 0, 0);
]],
	},
	method "data" {
		var_out{"const char *", "data", has_length = true},
		c_source [[
	${data} = ${this}->raw.data;
	${data}_len = ${this}->raw.len;
]],
	},
	method "set_data" {
		var_in{"const char *", "data"},
		c_source [[
	RawObject_set_data_and_ref(L, ${this}, ${data}, ${data}_len, ${data::idx});
]],
	},
	method "len" {
		var_out{"size_t", "len"},
		c_source [[
	${len} = ${this}->raw.len;
]],
	},
	method "type" {
		var_out{"const char *", "type"},
		c_source "${type} = git_object_type2string(${this}->raw.type);"
	},
	method "set_type" {
		var_in{"const char *", "type"},
		c_source "${this}->raw.type = git_object_string2type(${type});"
	},
	method "hash" {
		var_out{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_rawobj_hash(&(${id}), &(${this}->raw));
]],
	},
}

