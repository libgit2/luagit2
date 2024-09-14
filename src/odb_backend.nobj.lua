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

object "ODBBackend" {
	c_source [[
#include <git2/odb_backend.h>
#include <git2/sys/odb_backend.h>

typedef struct ODBBackend {
	git_odb_backend backend;
	lua_State *L;
	int read;
	int read_prefix;
	int read_header;
	int write;
	int exists;
	int free;
	int ref_count;
} ODBBackend;

static void ODBBackend_ref(ODBBackend *backend) {
	backend->ref_count++;
}

static void ODBBackend_unref(ODBBackend *backend) {
	lua_State *L = backend->L;
	assert(backend->ref_count > 0);
	if((--backend->ref_count) == 0) {
		luaL_unref(L, LUA_REGISTRYINDEX, backend->read);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->read_prefix);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->read_header);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->write);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->exists);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->free);
		free(backend);
	}
}

static int odb_backend_read_cb(void **data_p, size_t *len_p, git_otype *type_p, git_odb_backend *backend, const git_oid *oid)
{
	ODBBackend *lua_backend = (ODBBackend *)backend;
	lua_State *L = lua_backend->L;
	const char *ldata;
	size_t len;
	int err;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->read);

	obj_type_OID_push(L, *((OID *)oid));
	/* call Lua function. */
	lua_call(L, 1, 2);
	ldata = lua_tolstring(L, -2, &len);
	if(ldata) {
		char *data;
		/* parse otype value. */
		int arg_type = lua_type(L, -1);
		if(arg_type == LUA_TNUMBER) {
			*type_p = lua_tointeger(L, -1);
		} else if(arg_type == LUA_TSTRING) {
			*type_p = git_object_string2type(lua_tostring(L, -1));
		}
		*len_p = len;
		/* allocate buffer for data. */
		data = malloc(len);
		*data_p = data;
		if(data == NULL) {
			return GIT_EBUFS; //GIT_ENOMEM;
		}
		/* copy data. */
		memcpy(data, ldata, len);
		err = GIT_OK;
	} else if(lua_isnil(L, -2)) {
		*data_p = NULL;
		/* backend returned an error. */
		err = lua_tointeger(L, -1);
	} else {
		*data_p = NULL;
		/* bad return value from lua backend. */
		err = GIT_EAMBIGUOUS; //GIT_EOBJTYPE;
	}

	return err;
}

static int odb_backend_read_prefix_cb(git_oid *out_oid, void **data_p, size_t *len_p, git_otype *type_p, git_odb_backend *backend, const git_oid *short_oid, size_t len)
{
	*data_p = NULL;
	if(len >= GIT_OID_HEXSZ) {
		int rc = odb_backend_read_cb(data_p, len_p, type_p, backend, short_oid);
		if(rc == GIT_OK) {
			git_oid_cpy(out_oid, short_oid);
		}
		return rc;
	}
	return GIT_EAMBIGUOUS; //GIT_ENOTIMPLEMENTED;
}

static int odb_backend_read_header_cb(size_t *len_p, git_otype *type_p, git_odb_backend *backend, const git_oid *oid)
{
	ODBBackend *lua_backend = (ODBBackend *)backend;
	lua_State *L = lua_backend->L;
	int err;
	int arg_type;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->read_header);

	obj_type_OID_push(L, *((OID *)oid));
	/* call Lua function. */
	lua_call(L, 1, 2);

	arg_type = lua_type(L, -2);
	if(arg_type == LUA_TSTRING || arg_type == LUA_TNUMBER) {
		/* parse data length. */
		*len_p = lua_tonumber(L, -2);
		/* parse otype value. */
		lua_type(L, -1);
		if(arg_type == LUA_TNUMBER) {
			*type_p = lua_tointeger(L, -1);
		} else if(arg_type == LUA_TSTRING) {
			*type_p = git_object_string2type(lua_tostring(L, -1));
		}
		err = GIT_OK;
	} else if(arg_type == LUA_TNIL) {
		/* backend returned an error. */
		err = lua_tointeger(L, -1);
	} else {
		/* bad return value from lua backend. */
		err = GIT_EAMBIGUOUS; //GIT_EOBJTYPE;
	}

	return err;
}

static int odb_backend_write_cb(git_odb_backend *backend, const git_oid *oid, const void *data, size_t len, git_otype type)
{
	ODBBackend *lua_backend = (ODBBackend *)backend;
	lua_State *L = lua_backend->L;
	int err;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->write);

	/* push data onto stack. */
	lua_pushlstring(L, data, len);
	/* push otype */
	lua_pushstring(L, git_object_type2string(type));

	/* call Lua function. */
	lua_call(L, 2, 2);
	// TODO: this is bork
	if(!lua_isnil(L, -2)) {
		//*oid = obj_type_OID_check(L,-2);
		err = GIT_OK;
	} else {
		err = lua_tointeger(L, -1);
	}

	return err;
}

static int odb_backend_exists_cb(git_odb_backend *backend, const git_oid *oid)
{
	ODBBackend *lua_backend = (ODBBackend *)backend;
	lua_State *L = lua_backend->L;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->exists);

	obj_type_OID_push(L, *((OID *)oid));
	/* call Lua function. */
	lua_call(L, 1, 1);
	return lua_tointeger(L, -1);
}

static void odb_backend_free_cb(git_odb_backend *backend)
{
	ODBBackend *lua_backend = (ODBBackend *)backend;
	lua_State *L = lua_backend->L;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->free);

	/* call Lua function. */
	lua_call(L, 0, 0);

	ODBBackend_unref(lua_backend);
}

]],
	constructor {
		var_in{"lua_State *", "L"},
		c_source [[
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 1);
	/* create backend object. */
	${this} = calloc(1, sizeof(ODBBackend));
	${this}->ref_count = 1;
	${this}->L = L;
	/* get each callback from table. */
#define REF_CB(_name) \
	lua_getfield(L, 1, "on_" #_name); \
	${this}->_name = luaL_ref(L, LUA_REGISTRYINDEX); \
	${this}->backend._name = odb_backend_ ## _name ## _cb;

	REF_CB(read)
	REF_CB(read_prefix)
	REF_CB(read_header)
	REF_CB(write)
	REF_CB(exists)
	REF_CB(free)
#undef REF_CB

#ifdef GIT_ODB_BACKEND_VERSION
  ${this}->backend.version = GIT_ODB_BACKEND_VERSION;
#endif
]]
	},
	destructor {
		c_source [[
	ODBBackend_unref(${this});
]]
	},
}

