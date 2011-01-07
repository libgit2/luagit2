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
//typedef struct RawObject RawObject;
#include <git2/odb_backend.h>

typedef struct DatabaseBackend {
	git_odb_backend backend;
	lua_State *L;
	int read;
	int read_header;
	int write;
	int exists;
	int free;
	int ref_count;
} DatabaseBackend;

static void DatabaseBackend_ref(DatabaseBackend *backend) {
	backend->ref_count++;
}

static void DatabaseBackend_unref(DatabaseBackend *backend) {
	lua_State *L = backend->L;
	if((--backend->ref_count) == 0) {
		luaL_unref(L, LUA_REGISTRYINDEX, backend->read);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->read_header);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->write);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->exists);
		luaL_unref(L, LUA_REGISTRYINDEX, backend->free);
		free(backend);
	}
}

static int database_backend_read_cb(git_rawobj *obj, git_odb_backend *backend, const git_oid *oid)
{
	DatabaseBackend *lua_backend = (DatabaseBackend *)backend;
	lua_State *L = lua_backend->L;
	int err;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->read);

	obj_type_OID_push(L, *((OID *)oid), 0);
	/* call Lua function. */
	lua_call(L, 1, 2);
	err = lua_tointeger(L, -1);
	if(err == 0) {
		RawObject *raw_obj = obj_type_RawObject_check(L,-2);
		*obj = raw_obj->raw;
	}

	return err;
}

static int database_backend_read_header_cb(git_rawobj *obj, git_odb_backend *backend, const git_oid *oid)
{
	DatabaseBackend *lua_backend = (DatabaseBackend *)backend;
	lua_State *L = lua_backend->L;
	int err;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->read_header);

	obj_type_OID_push(L, *((OID *)oid), 0);
	/* call Lua function. */
	lua_call(L, 1, 2);
	err = lua_tointeger(L, -1);
	if(err == 0) {
		RawObject *raw_obj = obj_type_RawObject_check(L,-2);
		*obj = raw_obj->raw;
	}

	return err;
}

static int database_backend_write_cb(git_oid *oid, git_odb_backend *backend, git_rawobj *obj)
{
	DatabaseBackend *lua_backend = (DatabaseBackend *)backend;
	lua_State *L = lua_backend->L;
	RawObject raw;
	int err;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->write);

	/* convert git_rawobj to RawObject */
	RawObject_from_git_rawobj(L, &raw, obj);
	/* push RawObject onto stack. */
	obj_type_RawObject_push(L, &raw, 0);

	/* call Lua function. */
	lua_call(L, 1, 2);
	err = lua_tointeger(L, -1);
	if(err == 0) {
		*oid = obj_type_OID_check(L,-2);
	}

	return err;
}

static int database_backend_exists_cb(git_odb_backend *backend, const git_oid *oid)
{
	DatabaseBackend *lua_backend = (DatabaseBackend *)backend;
	lua_State *L = lua_backend->L;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->exists);

	obj_type_OID_push(L, *((OID *)oid), 0);
	/* call Lua function. */
	lua_call(L, 1, 1);
	return lua_tointeger(L, -1);
}

static void database_backend_free_cb(git_odb_backend *backend)
{
	DatabaseBackend *lua_backend = (DatabaseBackend *)backend;
	lua_State *L = lua_backend->L;

	/* get Lua callback function. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_backend->free);

	/* call Lua function. */
	lua_call(L, 0, 0);

	DatabaseBackend_unref(lua_backend);
}

]]

object "DatabaseBackend" {
	constructor {
		var_in{"lua_State *", "L"},
		c_source [[
	int idx;
	int ref;
	int priority = luaL_optinteger(L, 2, 0);

	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 1);
	/* create backend object. */
	${this} = calloc(1, sizeof(DatabaseBackend));
	${this}->ref_count = 1;
	${this}->L = L;
	/* get each callback from table. */
#define REF_CB(_name) \
	lua_getfield(L, 1, "on_" #_name); \
	${this}->_name = luaL_ref(L, LUA_REGISTRYINDEX); \
	${this}->backend._name = database_backend_ ## _name ## _cb;

	REF_CB(read)
	REF_CB(read_header)
	REF_CB(write)
	REF_CB(exists)
	REF_CB(free)
#undef REF_CB

	${this}->backend.priority = priority;
]]
	},
	destructor {
		c_source [[
	DatabaseBackend_unref(${this});
]]
	},
}

