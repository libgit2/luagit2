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
	git_rawobj git;
	int ref;
} RawObject;

static void RawObject_set_data_and_ref(lua_State *L, RawObject *raw, const char *data, int len, int idx) {
	/* Release old reference. */
	if(raw->ref != LUA_REFNIL) {
		luaL_unref(L, LUA_REGISTRYINDEX, raw->ref);
	}
	raw->git.data = (void *)data;
	raw->git.len = len;
	if(data) {
		/* Get a reference to the Lua string. */
		lua_pushvalue(L, idx);
		raw->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	} else {
		raw->ref = LUA_REFNIL;
	}
}

static void RawObject_from_git_rawobj(lua_State *L, RawObject *raw, const git_rawobj *git) {
  /* push raw object's data onto stack. */
  lua_pushlstring(L, git->data, git->len);
  /* get Lua's pointer to the string. */
  raw->git.data = (void *)lua_tolstring(L, -1, &(raw->git.len));
  raw->git.type = git->type;
  /* get reference to string. */
  raw->ref = luaL_ref(L, LUA_REGISTRYINDEX);
}

]]

object "RawObject" {
	userdata_type = 'embed',
	default = 'NULL',
	constructor {
		var_in{"const char *", "type"},
		var_in{"const char *", "data"},
		c_source [[
	RawObject raw; /* temp. storage, this gets copied. */
	${this} = &(raw);
	raw.git.type = git_object_string2type(${type});
	raw.ref = LUA_REFNIL;
	RawObject_set_data_and_ref(L, &raw, ${data}, ${data}_len, ${data::idx});
]],
	},
	destructor "close" {
		c_source [[
	luaL_unref(L, LUA_REGISTRYINDEX, ${this}->ref);
	${this}->ref = LUA_REFNIL;
	${this}->git.data = NULL;
	${this}->git.len = 0;
	RawObject_set_data_and_ref(L, ${this}, NULL, 0, 0);
]],
	},
	method "data" {
		var_out{"const char *", "data", has_length = true},
		c_source [[
	/* push Lua string. */
	// TODO: add support to directly push Lua values.
	//lua_rawgeti(L, LUA_REGISTRYINDEX, ${this}->ref);
	${data} = ${this}->git.data;
	${data}_len = ${this}->git.len;
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
	${len} = ${this}->git.len;
]],
	},
	method "type" {
		var_out{"const char *", "type"},
		c_source "${type} = git_object_type2string(${this}->git.type);"
	},
	method "set_type" {
		var_in{"const char *", "type"},
		c_source "${this}->git.type = git_object_string2type(${type});"
	},
	method "hash" {
		var_out{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_rawobj_hash(&(${id}), &(${this}->git));
]],
	},
}

