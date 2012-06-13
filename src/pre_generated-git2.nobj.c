/***********************************************************************************************
************************************************************************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!! Warning this file was generated from a set of *.nobj.lua definition files !!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
************************************************************************************************
***********************************************************************************************/

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define REG_PACKAGE_IS_CONSTRUCTOR 0
#define REG_MODULES_AS_GLOBALS 0
#define REG_OBJECTS_AS_GLOBALS 0
#define OBJ_DATA_HIDDEN_METATABLE 0
#define USE_FIELD_GET_SET_METHODS 0
#define LUAJIT_FFI 0


#include "git2.h"



#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#ifdef _MSC_VER
#define __WINDOWS__
#else
#if defined(_WIN32)
#define __WINDOWS__
#endif
#endif

#ifdef __WINDOWS__

/* for MinGW32 compiler need to include <stdint.h> */
#ifdef __GNUC__
#include <stdint.h>
#include <stdbool.h>
#else

/* define some standard types missing on Windows. */
#ifndef __INT32_MAX__
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
#ifndef __INT64_MAX__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef int bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#endif

/* wrap strerror_s(). */
#ifdef __GNUC__
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) do { \
	strncpy((buf), strerror(errno), (buflen)-1); \
	(buf)[(buflen)-1] = '\0'; \
} while(0)
#endif
#else
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) strerror_s((buf), (buflen), (errno))
#endif
#endif

#define FUNC_UNUSED

#define LUA_NOBJ_API __declspec(dllexport)

#else

#define LUA_NOBJ_API LUALIB_API

#include <stdint.h>
#include <stdbool.h>

#define FUNC_UNUSED __attribute__((unused))

#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define assert_obj_type(type, obj) \
	assert(__builtin_types_compatible_p(typeof(obj), type *))
#else
#define assert_obj_type(type, obj)
#endif

void *nobj_realloc(void *ptr, size_t osize, size_t nsize);

void *nobj_realloc(void *ptr, size_t osize, size_t nsize) {
	(void)osize;
	if(0 == nsize) {
		free(ptr);
		return NULL;
	}
	return realloc(ptr, nsize);
}

#define obj_type_free(type, obj) do { \
	assert_obj_type(type, obj); \
	nobj_realloc((obj), sizeof(type), 0); \
} while(0)

#define obj_type_new(type, obj) do { \
	assert_obj_type(type, obj); \
	(obj) = nobj_realloc(NULL, 0, sizeof(type)); \
} while(0)

typedef struct obj_type obj_type;

typedef void (*base_caster_t)(void **obj);

typedef void (*dyn_caster_t)(void **obj, obj_type **type);

#define OBJ_TYPE_FLAG_WEAK_REF (1<<0)
#define OBJ_TYPE_SIMPLE (1<<1)
struct obj_type {
	dyn_caster_t    dcaster;  /**< caster to support casting to sub-objects. */
	int32_t         id;       /**< type's id. */
	uint32_t        flags;    /**< type's flags (weak refs) */
	const char      *name;    /**< type's object name. */
};

typedef struct obj_base {
	int32_t        id;
	base_caster_t  bcaster;
} obj_base;

typedef enum obj_const_type {
	CONST_UNKOWN    = 0,
	CONST_BOOLEAN   = 1,
	CONST_NUMBER    = 2,
	CONST_STRING    = 3
} obj_const_type;

typedef struct obj_const {
	const char      *name;    /**< constant's name. */
	const char      *str;
	double          num;
	obj_const_type  type;
} obj_const;

typedef enum obj_field_type {
	TYPE_UNKOWN    = 0,
	TYPE_UINT8     = 1,
	TYPE_UINT16    = 2,
	TYPE_UINT32    = 3,
	TYPE_UINT64    = 4,
	TYPE_INT8      = 5,
	TYPE_INT16     = 6,
	TYPE_INT32     = 7,
	TYPE_INT64     = 8,
	TYPE_DOUBLE    = 9,
	TYPE_FLOAT     = 10,
	TYPE_STRING    = 11
} obj_field_type;

typedef struct obj_field {
	const char      *name;  /**< field's name. */
	uint32_t        offset; /**< offset to field's data. */
	obj_field_type  type;   /**< field's data type. */
	uint32_t        flags;  /**< is_writable:1bit */
} obj_field;

typedef enum {
	REG_OBJECT,
	REG_PACKAGE,
	REG_META,
} module_reg_type;

typedef struct reg_sub_module {
	obj_type        *type;
	module_reg_type req_type;
	const luaL_reg  *pub_funcs;
	const luaL_reg  *methods;
	const luaL_reg  *metas;
	const obj_base  *bases;
	const obj_field *fields;
	const obj_const *constants;
	int             bidirectional_consts;
} reg_sub_module;

#define OBJ_UDATA_FLAG_OWN (1<<0)
#define OBJ_UDATA_FLAG_LOOKUP (1<<1)
#define OBJ_UDATA_LAST_FLAG (OBJ_UDATA_FLAG_LOOKUP)
typedef struct obj_udata {
	void     *obj;
	uint32_t flags;  /**< lua_own:1bit */
} obj_udata;

/* use static pointer as key to weak userdata table. */
static char obj_udata_weak_ref_key[] = "obj_udata_weak_ref_key";

/* use static pointer as key to module's private table. */
static char obj_udata_private_key[] = "obj_udata_private_key";

#if LUAJIT_FFI
typedef int (*ffi_export_func_t)(void);
typedef struct ffi_export_symbol {
	const char *name;
	union {
	void               *data;
	ffi_export_func_t  func;
	} sym;
} ffi_export_symbol;
#endif



typedef int GitError;

static void error_code__GitError__push(lua_State *L, GitError err);
static void dyn_caster_Object(void **obj, obj_type **type);


static obj_type obj_types[] = {
#define obj_type_id_StrArray 0
#define obj_type_StrArray (obj_types[obj_type_id_StrArray])
  { NULL, 0, OBJ_TYPE_SIMPLE, "StrArray" },
#define obj_type_id_Repository 1
#define obj_type_Repository (obj_types[obj_type_id_Repository])
  { NULL, 1, OBJ_TYPE_FLAG_WEAK_REF, "Repository" },
#define obj_type_id_Config 2
#define obj_type_Config (obj_types[obj_type_id_Config])
  { NULL, 2, OBJ_TYPE_FLAG_WEAK_REF, "Config" },
#define obj_type_id_OdbObject 3
#define obj_type_OdbObject (obj_types[obj_type_id_OdbObject])
  { NULL, 3, OBJ_TYPE_FLAG_WEAK_REF, "OdbObject" },
#define obj_type_id_OID 4
#define obj_type_OID (obj_types[obj_type_id_OID])
  { NULL, 4, OBJ_TYPE_SIMPLE, "OID" },
#define obj_type_id_OID_Shorten 5
#define obj_type_OID_Shorten (obj_types[obj_type_id_OID_Shorten])
  { NULL, 5, OBJ_TYPE_FLAG_WEAK_REF, "OID_Shorten" },
#define obj_type_id_ODB 6
#define obj_type_ODB (obj_types[obj_type_id_ODB])
  { NULL, 6, OBJ_TYPE_FLAG_WEAK_REF, "ODB" },
#define obj_type_id_ODBBackend 7
#define obj_type_ODBBackend (obj_types[obj_type_id_ODBBackend])
  { NULL, 7, OBJ_TYPE_FLAG_WEAK_REF, "ODBBackend" },
#define obj_type_id_Index 8
#define obj_type_Index (obj_types[obj_type_id_Index])
  { NULL, 8, OBJ_TYPE_FLAG_WEAK_REF, "Index" },
#define obj_type_id_IndexEntry 9
#define obj_type_IndexEntry (obj_types[obj_type_id_IndexEntry])
  { NULL, 9, OBJ_TYPE_FLAG_WEAK_REF, "IndexEntry" },
#define obj_type_id_IndexEntryUnmerged 10
#define obj_type_IndexEntryUnmerged (obj_types[obj_type_id_IndexEntryUnmerged])
  { NULL, 10, OBJ_TYPE_FLAG_WEAK_REF, "IndexEntryUnmerged" },
#define obj_type_id_Object 11
#define obj_type_Object (obj_types[obj_type_id_Object])
  { dyn_caster_Object, 11, OBJ_TYPE_FLAG_WEAK_REF, "Object" },
#define obj_type_id_Blob 12
#define obj_type_Blob (obj_types[obj_type_id_Blob])
  { NULL, 12, OBJ_TYPE_FLAG_WEAK_REF, "Blob" },
#define obj_type_id_Signature 13
#define obj_type_Signature (obj_types[obj_type_id_Signature])
  { NULL, 13, OBJ_TYPE_FLAG_WEAK_REF, "Signature" },
#define obj_type_id_Commit 14
#define obj_type_Commit (obj_types[obj_type_id_Commit])
  { NULL, 14, OBJ_TYPE_FLAG_WEAK_REF, "Commit" },
#define obj_type_id_Tree 15
#define obj_type_Tree (obj_types[obj_type_id_Tree])
  { NULL, 15, OBJ_TYPE_FLAG_WEAK_REF, "Tree" },
#define obj_type_id_TreeEntry 16
#define obj_type_TreeEntry (obj_types[obj_type_id_TreeEntry])
  { NULL, 16, OBJ_TYPE_FLAG_WEAK_REF, "TreeEntry" },
#define obj_type_id_Tag 17
#define obj_type_Tag (obj_types[obj_type_id_Tag])
  { NULL, 17, OBJ_TYPE_FLAG_WEAK_REF, "Tag" },
#define obj_type_id_RevWalk 18
#define obj_type_RevWalk (obj_types[obj_type_id_RevWalk])
  { NULL, 18, OBJ_TYPE_FLAG_WEAK_REF, "RevWalk" },
#define obj_type_id_Reference 19
#define obj_type_Reference (obj_types[obj_type_id_Reference])
  { NULL, 19, OBJ_TYPE_FLAG_WEAK_REF, "Reference" },
  {NULL, -1, 0, NULL},
};


#if LUAJIT_FFI

/* nobj_ffi_support_enabled_hint should be set to 1 when FFI support is enabled in at-least one
 * instance of a LuaJIT state.  It should never be set back to 0. */
static int nobj_ffi_support_enabled_hint = 0;
static const char nobj_ffi_support_key[] = "LuaNativeObject_FFI_SUPPORT";
static const char nobj_check_ffi_support_code[] =
"local stat, ffi=pcall(require,\"ffi\")\n" /* try loading LuaJIT`s FFI module. */
"if not stat then return false end\n"
"return true\n";

static int nobj_check_ffi_support(lua_State *L) {
	int rc;
	int err;

	/* check if ffi test has already been done. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_rawget(L, LUA_REGISTRYINDEX);
	if(!lua_isnil(L, -1)) {
		rc = lua_toboolean(L, -1);
		lua_pop(L, 1);
		/* use results of previous check. */
		goto finished;
	}
	lua_pop(L, 1); /* pop nil. */

	err = luaL_loadbuffer(L, nobj_check_ffi_support_code,
		sizeof(nobj_check_ffi_support_code) - 1, nobj_ffi_support_key);
	if(0 == err) {
		err = lua_pcall(L, 0, 1, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Error when checking for FFI-support: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
		return 0;
	}
	/* check results of test. */
	rc = lua_toboolean(L, -1);
	lua_pop(L, 1); /* pop results. */
		/* cache results. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_pushboolean(L, rc);
	lua_rawset(L, LUA_REGISTRYINDEX);

finished:
	/* turn-on hint that there is FFI code enabled. */
	if(rc) {
		nobj_ffi_support_enabled_hint = 1;
	}

	return rc;
}

typedef struct {
	const char **ffi_init_code;
	int offset;
} nobj_reader_state;

static const char *nobj_lua_Reader(lua_State *L, void *data, size_t *size) {
	nobj_reader_state *state = (nobj_reader_state *)data;
	const char *ptr;

	(void)L;
	ptr = state->ffi_init_code[state->offset];
	if(ptr != NULL) {
		*size = strlen(ptr);
		state->offset++;
	} else {
		*size = 0;
	}
	return ptr;
}

static int nobj_try_loading_ffi(lua_State *L, const char *ffi_mod_name,
		const char *ffi_init_code[], const ffi_export_symbol *ffi_exports, int priv_table)
{
	nobj_reader_state state = { ffi_init_code, 0 };
	int err;

	/* export symbols to priv_table. */
	while(ffi_exports->name != NULL) {
		lua_pushstring(L, ffi_exports->name);
		lua_pushlightuserdata(L, ffi_exports->sym.data);
		lua_settable(L, priv_table);
		ffi_exports++;
	}
	err = lua_load(L, nobj_lua_Reader, &state, ffi_mod_name);
	if(0 == err) {
		lua_pushvalue(L, -2); /* dup C module's table. */
		lua_pushvalue(L, priv_table); /* move priv_table to top of stack. */
		lua_remove(L, priv_table);
		lua_pushvalue(L, LUA_REGISTRYINDEX);
		err = lua_pcall(L, 3, 0, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Failed to install FFI-based bindings: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
	}
	return err;
}
#endif

#ifndef REG_PACKAGE_IS_CONSTRUCTOR
#define REG_PACKAGE_IS_CONSTRUCTOR 1
#endif

#ifndef REG_MODULES_AS_GLOBALS
#define REG_MODULES_AS_GLOBALS 0
#endif

#ifndef REG_OBJECTS_AS_GLOBALS
#define REG_OBJECTS_AS_GLOBALS 0
#endif

#ifndef OBJ_DATA_HIDDEN_METATABLE
#define OBJ_DATA_HIDDEN_METATABLE 1
#endif

static FUNC_UNUSED obj_udata *obj_udata_toobj(lua_State *L, int _index) {
	obj_udata *ud;
	size_t len;

	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	/* verify userdata size. */
	len = lua_objlen(L, _index);
	if(len != sizeof(obj_udata)) {
		/* This shouldn't be possible */
		luaL_error(L, "invalid userdata size: size=%d, expected=%d", len, sizeof(obj_udata));
	}
	return ud;
}

static FUNC_UNUSED int obj_udata_is_compatible(lua_State *L, obj_udata *ud, void **obj, base_caster_t *caster, obj_type *type) {
	obj_base *base;
	obj_type *ud_type;
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(lua_rawequal(L, -1, -2)) {
		*obj = ud->obj;
		/* same type no casting needed. */
		return 1;
	} else {
		/* Different types see if we can cast to the required type. */
		lua_rawgeti(L, -2, type->id);
		base = lua_touserdata(L, -1);
		lua_pop(L, 1); /* pop obj_base or nil */
		if(base != NULL) {
			*caster = base->bcaster;
			/* get the obj_type for this userdata. */
			lua_pushliteral(L, ".type");
			lua_rawget(L, -3); /* type's metatable. */
			ud_type = lua_touserdata(L, -1);
			lua_pop(L, 1); /* pop obj_type or nil */
			if(base == NULL) {
				luaL_error(L, "bad userdata, missing type info.");
				return 0;
			}
			/* check if userdata is a simple object. */
			if(ud_type->flags & OBJ_TYPE_SIMPLE) {
				*obj = ud;
			} else {
				*obj = ud->obj;
			}
			return 1;
		}
	}
	return 0;
}

static FUNC_UNUSED obj_udata *obj_udata_luacheck_internal(lua_State *L, int _index, void **obj, obj_type *type, int not_delete) {
	obj_udata *ud;
	base_caster_t caster = NULL;
	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			if(obj_udata_is_compatible(L, ud, obj, &(caster), type)) {
				lua_pop(L, 2); /* pop both metatables. */
				/* apply caster function if needed. */
				if(caster != NULL && *obj != NULL) {
					caster(obj);
				}
				/* check object pointer. */
				if(*obj == NULL) {
					if(not_delete) {
						luaL_error(L, "null %s", type->name); /* object was garbage collected? */
					}
					return NULL;
				}
				return ud;
			}
		}
	} else if(!lua_isnil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				*obj = *(void **)lua_topointer(L, _index);
				return ud;
			}
			lua_pop(L, 2);
		} else {
			lua_pop(L, 1);
		}
	}
	if(not_delete) {
		luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	}
	return NULL;
}

static FUNC_UNUSED void *obj_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	if(lua_isnil(L, _index)) {
		return obj;
	}
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;
	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);
}

static FUNC_UNUSED void *obj_udata_luadelete_weak(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* remove object from weak table. */
	lua_pushlightuserdata(L, obj);
	lua_pushnil(L);
	lua_rawset(L, -3);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush_weak(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;

	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* lookup userdata instance from pointer. */
	lua_pushlightuserdata(L, obj);
	lua_rawget(L, -2);
	if(!lua_isnil(L, -1)) {
		lua_remove(L, -2);     /* remove objects table. */
		return;
	}
	lua_pop(L, 1);  /* pop nil. */

#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		lua_remove(L, -2);
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));

	/* init. obj_udata. */
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	/* add weak reference to object. */
	lua_pushlightuserdata(L, obj); /* push object pointer as the 'key' */
	lua_pushvalue(L, -2);          /* push object's udata */
	lua_rawset(L, -4);             /* add weak reference to object. */
	lua_remove(L, -2);     /* remove objects table. */
}

/* default object equal method. */
static FUNC_UNUSED int obj_udata_default_equal(lua_State *L) {
	obj_udata *ud1 = obj_udata_toobj(L, 1);
	obj_udata *ud2 = obj_udata_toobj(L, 2);

	lua_pushboolean(L, (ud1->obj == ud2->obj));
	return 1;
}

/* default object tostring method. */
static FUNC_UNUSED int obj_udata_default_tostring(lua_State *L) {
	obj_udata *ud = obj_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p, flags=%d", ud->obj, ud->flags);
	lua_concat(L, 2);

	return 1;
}

/*
 * Simple userdata objects.
 */
static FUNC_UNUSED void *obj_simple_udata_toobj(lua_State *L, int _index) {
	void *ud;

	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	return ud;
}

static FUNC_UNUSED void * obj_simple_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *ud;
	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			lua_pushlightuserdata(L, type);
			lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
			if(lua_rawequal(L, -1, -2)) {
				lua_pop(L, 2); /* pop both metatables. */
				return ud;
			}
		}
	} else if(!lua_isnil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				return (void *)lua_topointer(L, _index);
			}
		}
	}
	luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	return NULL;
}

static FUNC_UNUSED void * obj_simple_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	if(lua_isnil(L, _index)) {
		return NULL;
	}
	return obj_simple_udata_luacheck(L, _index, type);
}

static FUNC_UNUSED void * obj_simple_udata_luadelete(lua_State *L, int _index, obj_type *type) {
	void *obj;
	obj = obj_simple_udata_luacheck(L, _index, type);
	/* clear the metatable to invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void *obj_simple_udata_luapush(lua_State *L, void *obj, int size, obj_type *type)
{
	void *ud;
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_call(L, 1, 1);
		return obj;
	}
#endif
	/* create new userdata. */
	ud = lua_newuserdata(L, size);
	memcpy(ud, obj, size);
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	return ud;
}

/* default simple object equal method. */
static FUNC_UNUSED int obj_simple_udata_default_equal(lua_State *L) {
	void *ud1 = obj_simple_udata_toobj(L, 1);
	size_t len1 = lua_objlen(L, 1);
	void *ud2 = obj_simple_udata_toobj(L, 2);
	size_t len2 = lua_objlen(L, 2);

	if(len1 == len2) {
		lua_pushboolean(L, (memcmp(ud1, ud2, len1) == 0));
	} else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

/* default simple object tostring method. */
static FUNC_UNUSED int obj_simple_udata_default_tostring(lua_State *L) {
	void *ud = obj_simple_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p", ud);
	lua_concat(L, 2);

	return 1;
}

static int obj_constructor_call_wrapper(lua_State *L) {
	/* replace '__call' table with constructor function. */
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_replace(L, 1);

	/* call constructor function with all parameters after the '__call' table. */
	lua_call(L, lua_gettop(L) - 1, LUA_MULTRET);
	/* return all results from constructor. */
	return lua_gettop(L);
}

static void obj_type_register_constants(lua_State *L, const obj_const *constants, int tab_idx,
		int bidirectional) {
	/* register constants. */
	while(constants->name != NULL) {
		lua_pushstring(L, constants->name);
		switch(constants->type) {
		case CONST_BOOLEAN:
			lua_pushboolean(L, constants->num != 0.0);
			break;
		case CONST_NUMBER:
			lua_pushnumber(L, constants->num);
			break;
		case CONST_STRING:
			lua_pushstring(L, constants->str);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		/* map values back to keys. */
		if(bidirectional) {
			/* check if value already exists. */
			lua_pushvalue(L, -1);
			lua_rawget(L, tab_idx - 3);
			if(lua_isnil(L, -1)) {
				lua_pop(L, 1);
				/* add value->key mapping. */
				lua_pushvalue(L, -1);
				lua_pushvalue(L, -3);
				lua_rawset(L, tab_idx - 4);
			} else {
				/* value already exists. */
				lua_pop(L, 1);
			}
		}
		lua_rawset(L, tab_idx - 2);
		constants++;
	}
}

static void obj_type_register_package(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_reg *reg_list = type_reg->pub_funcs;

	/* create public functions table. */
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	lua_pop(L, 1);  /* drop package table */
}

static void obj_type_register_meta(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_reg *reg_list;

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	/* register methods. */
	luaL_register(L, NULL, type_reg->methods);

	/* create metatable table. */
	lua_newtable(L);
	luaL_register(L, NULL, type_reg->metas); /* fill metatable */
	/* setmetatable on meta-object. */
	lua_setmetatable(L, -2);

	lua_pop(L, 1);  /* drop meta-object */
}

static void obj_type_register(lua_State *L, const reg_sub_module *type_reg, int priv_table) {
	const luaL_reg *reg_list;
	obj_type *type = type_reg->type;
	const obj_base *base = type_reg->bases;

	if(type_reg->req_type == REG_PACKAGE) {
		obj_type_register_package(L, type_reg);
		return;
	}
	if(type_reg->req_type == REG_META) {
		obj_type_register_meta(L, type_reg);
		return;
	}

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register "constructors" as to object's public API */
		luaL_register(L, NULL, reg_list); /* fill public API table. */

		/* make public API table callable as the default constructor. */
		lua_newtable(L); /* create metatable */
		lua_pushliteral(L, "__call");
		lua_pushcfunction(L, reg_list[0].func); /* push first constructor function. */
		lua_pushcclosure(L, obj_constructor_call_wrapper, 1); /* make __call wrapper. */
		lua_rawset(L, -3);         /* metatable.__call = <default constructor> */

#if OBJ_DATA_HIDDEN_METATABLE
		lua_pushliteral(L, "__metatable");
		lua_pushboolean(L, 0);
		lua_rawset(L, -3);         /* metatable.__metatable = false */
#endif

		/* setmetatable on public API table. */
		lua_setmetatable(L, -2);

		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
	} else {
		/* register all methods as public functions. */
#if OBJ_DATA_HIDDEN_METATABLE
		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
#endif
	}

	luaL_register(L, NULL, type_reg->methods); /* fill methods table. */

	luaL_newmetatable(L, type->name); /* create metatable */
	lua_pushliteral(L, ".name");
	lua_pushstring(L, type->name);
	lua_rawset(L, -3);    /* metatable['.name'] = "<object_name>" */
	lua_pushliteral(L, ".type");
	lua_pushlightuserdata(L, type);
	lua_rawset(L, -3);    /* metatable['.type'] = lightuserdata -> obj_type */
	lua_pushlightuserdata(L, type);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, LUA_REGISTRYINDEX);    /* REGISTRY[type] = metatable */

	/* add metatable to 'priv_table' */
	lua_pushstring(L, type->name);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, priv_table);    /* priv_table["<object_name>"] = metatable */

	luaL_register(L, NULL, type_reg->metas); /* fill metatable */

	/* add obj_bases to metatable. */
	while(base->id >= 0) {
		lua_pushlightuserdata(L, (void *)base);
		lua_rawseti(L, -2, base->id);
		base++;
	}

	obj_type_register_constants(L, type_reg->constants, -2, type_reg->bidirectional_consts);

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table */
	lua_rawset(L, -3);                  /* metatable.__index = methods */
#if OBJ_DATA_HIDDEN_METATABLE
	lua_pushliteral(L, "__metatable");
	lua_pushboolean(L, 0);
	lua_rawset(L, -3);                  /* hide metatable:
	                                       metatable.__metatable = false */
#endif
	lua_pop(L, 2);                      /* drop metatable & methods */
}

static FUNC_UNUSED int lua_checktype_ref(lua_State *L, int _index, int _type) {
	luaL_checktype(L,_index,_type);
	lua_pushvalue(L,_index);
	return luaL_ref(L, LUA_REGISTRYINDEX);
}



#define obj_type_StrArray_check(L, _index) \
	(StrArray *)obj_simple_udata_luacheck(L, _index, &(obj_type_StrArray))
#define obj_type_StrArray_optional(L, _index) \
	(StrArray *)obj_simple_udata_luaoptional(L, _index, &(obj_type_StrArray))
#define obj_type_StrArray_delete(L, _index) \
	(StrArray *)obj_simple_udata_luadelete(L, _index, &(obj_type_StrArray))
#define obj_type_StrArray_push(L, obj) \
	obj_simple_udata_luapush(L, obj, sizeof(StrArray), &(obj_type_StrArray))

#define obj_type_Repository_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Repository))
#define obj_type_Repository_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Repository))
#define obj_type_Repository_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Repository), flags)
#define obj_type_Repository_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Repository), flags)

#define obj_type_Config_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Config))
#define obj_type_Config_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Config))
#define obj_type_Config_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Config), flags)
#define obj_type_Config_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Config), flags)

#define obj_type_OdbObject_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_OdbObject))
#define obj_type_OdbObject_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_OdbObject))
#define obj_type_OdbObject_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_OdbObject), flags)
#define obj_type_OdbObject_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_OdbObject), flags)

#define obj_type_OID_check(L, _index) \
	*((OID *)obj_simple_udata_luacheck(L, _index, &(obj_type_OID)))
#define obj_type_OID_optional(L, _index) \
	*((OID *)obj_simple_udata_luaoptional(L, _index, &(obj_type_OID)))
#define obj_type_OID_delete(L, _index) \
	*((OID *)obj_simple_udata_luadelete(L, _index, &(obj_type_OID)))
#define obj_type_OID_push(L, obj) \
	obj_simple_udata_luapush(L, &(obj), sizeof(OID), &(obj_type_OID))

#define obj_type_OID_Shorten_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_OID_Shorten))
#define obj_type_OID_Shorten_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_OID_Shorten))
#define obj_type_OID_Shorten_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_OID_Shorten), flags)
#define obj_type_OID_Shorten_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_OID_Shorten), flags)

#define obj_type_ODB_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_ODB))
#define obj_type_ODB_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_ODB))
#define obj_type_ODB_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_ODB), flags)
#define obj_type_ODB_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_ODB), flags)

#define obj_type_ODBBackend_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_ODBBackend))
#define obj_type_ODBBackend_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_ODBBackend))
#define obj_type_ODBBackend_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_ODBBackend), flags)
#define obj_type_ODBBackend_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_ODBBackend), flags)

#define obj_type_Index_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Index))
#define obj_type_Index_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Index))
#define obj_type_Index_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Index), flags)
#define obj_type_Index_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Index), flags)

#define obj_type_IndexEntry_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_IndexEntry))
#define obj_type_IndexEntry_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_IndexEntry))
#define obj_type_IndexEntry_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_IndexEntry), flags)
#define obj_type_IndexEntry_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_IndexEntry), flags)

#define obj_type_IndexEntryUnmerged_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_IndexEntryUnmerged))
#define obj_type_IndexEntryUnmerged_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_IndexEntryUnmerged))
#define obj_type_IndexEntryUnmerged_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_IndexEntryUnmerged), flags)
#define obj_type_IndexEntryUnmerged_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_IndexEntryUnmerged), flags)

#define obj_type_Object_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Object))
#define obj_type_Object_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Object))
#define obj_type_Object_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Object), flags)
#define obj_type_Object_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Object), flags)

#define obj_type_Blob_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Blob))
#define obj_type_Blob_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Blob))
#define obj_type_Blob_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Blob), flags)
#define obj_type_Blob_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Blob), flags)

#define obj_type_Signature_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Signature))
#define obj_type_Signature_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Signature))
#define obj_type_Signature_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Signature), flags)
#define obj_type_Signature_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Signature), flags)

#define obj_type_Commit_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Commit))
#define obj_type_Commit_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Commit))
#define obj_type_Commit_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Commit), flags)
#define obj_type_Commit_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Commit), flags)

#define obj_type_Tree_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Tree))
#define obj_type_Tree_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Tree))
#define obj_type_Tree_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Tree), flags)
#define obj_type_Tree_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Tree), flags)

#define obj_type_TreeEntry_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_TreeEntry))
#define obj_type_TreeEntry_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_TreeEntry))
#define obj_type_TreeEntry_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_TreeEntry), flags)
#define obj_type_TreeEntry_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_TreeEntry), flags)

#define obj_type_Tag_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Tag))
#define obj_type_Tag_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Tag))
#define obj_type_Tag_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Tag), flags)
#define obj_type_Tag_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Tag), flags)

#define obj_type_RevWalk_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_RevWalk))
#define obj_type_RevWalk_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_RevWalk))
#define obj_type_RevWalk_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_RevWalk), flags)
#define obj_type_RevWalk_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_RevWalk), flags)

#define obj_type_Reference_check(L, _index) \
	obj_udata_luacheck(L, _index, &(obj_type_Reference))
#define obj_type_Reference_optional(L, _index) \
	obj_udata_luaoptional(L, _index, &(obj_type_Reference))
#define obj_type_Reference_delete(L, _index, flags) \
	obj_udata_luadelete_weak(L, _index, &(obj_type_Reference), flags)
#define obj_type_Reference_push(L, obj, flags) \
	obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Reference), flags)



typedef git_strarray StrArray;

typedef git_repository Repository;

typedef git_config Config;

typedef git_odb_object OdbObject;

typedef git_oid OID;

typedef git_oid_shorten OID_Shorten;

typedef git_odb ODB;

#include <git2/odb_backend.h>

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

static int odb_backend_read_prefix_cb(git_oid *out_oid, void **data_p, size_t *len_p, git_otype *type_p, git_odb_backend *backend, const git_oid *short_oid, unsigned int len)
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

static int odb_backend_write_cb(git_oid *oid, git_odb_backend *backend, const void *data, size_t len, git_otype type)
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
	if(!lua_isnil(L, -2)) {
		*oid = obj_type_OID_check(L,-2);
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


typedef git_index Index;

typedef git_index_entry IndexEntry;

typedef git_index_entry_unmerged IndexEntryUnmerged;

typedef git_object Object;


typedef git_blob Blob;

typedef git_signature Signature;


typedef git_commit Commit;


typedef git_tree Tree;

typedef git_tree_entry TreeEntry;


typedef git_tag Tag;

typedef git_revwalk RevWalk;

typedef git_reference Reference;



/* method: version */
static int git2__version__func(lua_State *L) {
	int major, minor, patch;
	git_libgit2_version(&(major), &(minor), &(patch));

	/* return version as a table: { major, minor, patch } */
	lua_createtable(L, 3, 0);
	lua_pushinteger(L, major);
	lua_rawseti(L, -2, 1);
	lua_pushinteger(L, minor);
	lua_rawseti(L, -2, 2);
	lua_pushinteger(L, patch);
	lua_rawseti(L, -2, 3);

  return 1;
}

/* method: new */
static int StrArray__new__meth(lua_State *L) {
  StrArray this_idx1_store;
  StrArray * this_idx1 = &(this_idx1_store);
	StrArray array;
	array.strings = NULL;
	array.count = 0;
	this_idx1 = &array;

  obj_type_StrArray_push(L, this_idx1);
  return 1;
}

/* method: free */
static int StrArray__free__meth(lua_State *L) {
  StrArray * this_idx1 = obj_type_StrArray_delete(L,1);
	if(this_idx1->strings != 0) {
		git_strarray_free(this_idx1);
		this_idx1->strings = NULL;
	}

  return 0;
}

/* method: str */
static int StrArray__str__meth(lua_State *L) {
  StrArray * this_idx1 = obj_type_StrArray_check(L,1);
  size_t n_idx2 = luaL_checkinteger(L,2);
  const char * str_idx1 = NULL;
	if(n_idx2 < this_idx1->count) {
		str_idx1 = this_idx1->strings[n_idx2];
	}

  lua_pushstring(L, str_idx1);
  return 1;
}

/* method: get_array */
static int StrArray__get_array__meth(lua_State *L) {
  StrArray * this_idx1 = obj_type_StrArray_check(L,1);
	size_t n;

	lua_createtable(L, this_idx1->count, 0);
	for(n = 0; n < this_idx1->count; n++) {
		lua_pushstring(L, this_idx1->strings[n]);
		lua_rawseti(L, -2, n+1);
	}

  return 1;
}

/* method: count */
static int StrArray__count__meth(lua_State *L) {
  StrArray * this_idx1 = obj_type_StrArray_check(L,1);
  size_t field_idx1 = 0;
	field_idx1 = this_idx1->count;

  lua_pushinteger(L, field_idx1);
  return 1;
}

static void error_code__GitError__push(lua_State *L, GitError err) {
  const char *err_str = NULL;
	const git_error *giterr;
	switch(err) {
	case GIT_ERROR:
		giterr = giterr_last();
		err_str = giterr->message;
		break;
	case GIT_ENOTFOUND:
		err_str = "ENOTFOUND";
		break;
	case GIT_EEXISTS:
		err_str = "EEXISTS";
		break;
	case GIT_EAMBIGUOUS:
		err_str = "EAMBIGUOUS";
		break;
	case GIT_EBUFS:
		err_str = "EBUFS";
		break;
	case GIT_PASSTHROUGH:
		err_str = "PASSTHROUGH";
		break;
	case GIT_REVWALKOVER:
		err_str = "REVWALKOVER";
		break;
	case GIT_OK:
	default:
		break;
	}

	if(err_str) {
		lua_pushstring(L, err_str);
	} else {
		lua_pushnil(L);
	}
}

/* method: open */
static int Repository__open__meth(lua_State *L) {
  size_t path_len_idx1;
  const char * path_idx1 = luaL_checklstring(L,1,&(path_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Repository * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_repository_open(&(this_idx1), path_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Repository_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: init */
static int Repository__init__meth(lua_State *L) {
  size_t path_len_idx1;
  const char * path_idx1 = luaL_checklstring(L,1,&(path_len_idx1));
  unsigned int is_bare_idx2 = luaL_checkinteger(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Repository * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_repository_init(&(this_idx1), path_idx1, is_bare_idx2);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Repository_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: _priv */
static int Repository__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Repository * this_idx1 = obj_type_Repository_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_repository_free(this_idx1);
  return 0;
}

/* method: head */
static int Repository__head__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  int head_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Reference * head_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_repository_head(&(head_idx1), this_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Reference_push(L, head_idx1, head_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: head_detached */
static int Repository__head_detached__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  bool rc_git_repository_head_detached_idx1 = 0;
  rc_git_repository_head_detached_idx1 = git_repository_head_detached(this_idx1);
  lua_pushboolean(L, rc_git_repository_head_detached_idx1);
  return 1;
}

/* method: head_orphan */
static int Repository__head_orphan__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  bool rc_git_repository_head_orphan_idx1 = 0;
  rc_git_repository_head_orphan_idx1 = git_repository_head_orphan(this_idx1);
  lua_pushboolean(L, rc_git_repository_head_orphan_idx1);
  return 1;
}

/* method: is_empty */
static int Repository__is_empty__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  bool rc_git_repository_is_empty_idx1 = 0;
  rc_git_repository_is_empty_idx1 = git_repository_is_empty(this_idx1);
  lua_pushboolean(L, rc_git_repository_is_empty_idx1);
  return 1;
}

/* method: is_bare */
static int Repository__is_bare__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  bool rc_git_repository_is_bare_idx1 = 0;
  rc_git_repository_is_bare_idx1 = git_repository_is_bare(this_idx1);
  lua_pushboolean(L, rc_git_repository_is_bare_idx1);
  return 1;
}

/* method: path */
static int Repository__path__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  const char * rc_git_repository_path_idx1 = NULL;
  rc_git_repository_path_idx1 = git_repository_path(this_idx1);
  lua_pushstring(L, rc_git_repository_path_idx1);
  return 1;
}

/* method: workdir */
static int Repository__workdir__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  const char * rc_git_repository_workdir_idx1 = NULL;
  rc_git_repository_workdir_idx1 = git_repository_workdir(this_idx1);
  lua_pushstring(L, rc_git_repository_workdir_idx1);
  return 1;
}

/* method: set_workdir */
static int Repository__set_workdir__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  size_t workdir_len_idx2;
  const char * workdir_idx2 = luaL_checklstring(L,2,&(workdir_len_idx2));
  GitError rc_git_repository_set_workdir_idx1 = GIT_OK;
  rc_git_repository_set_workdir_idx1 = git_repository_set_workdir(this_idx1, workdir_idx2);
  /* check for error. */
  if((GIT_OK != rc_git_repository_set_workdir_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_repository_set_workdir_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: config */
static int Repository__config__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  int config_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Config * config_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_repository_config(&(config_idx1), this_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Config_push(L, config_idx1, config_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_config */
static int Repository__set_config__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  Config * config_idx2 = obj_type_Config_check(L,2);
  git_repository_set_config(this_idx1, config_idx2);
  return 0;
}

/* method: odb */
static int Repository__odb__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  int odb_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  ODB * odb_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_repository_odb(&(odb_idx1), this_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_ODB_push(L, odb_idx1, odb_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_odb */
static int Repository__set_odb__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  ODB * odb_idx2 = obj_type_ODB_check(L,2);
  git_repository_set_odb(this_idx1, odb_idx2);
  return 0;
}

/* method: index */
static int Repository__index__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  int index_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Index * index_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_repository_index(&(index_idx1), this_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Index_push(L, index_idx1, index_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_index */
static int Repository__set_index__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  Index * index_idx2 = obj_type_Index_check(L,2);
  git_repository_set_index(this_idx1, index_idx2);
  return 0;
}

/* method: new */
static int Config__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Config * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_config_new(&(this_idx1));
  if(!(GIT_OK != err_idx2)) {
    obj_type_Config_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: open */
static int Config__open__meth(lua_State *L) {
  size_t path_len_idx1;
  const char * path_idx1 = luaL_checklstring(L,1,&(path_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Config * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_config_open_ondisk(&(this_idx1), path_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Config_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: free */
static int Config__free__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Config * this_idx1 = obj_type_Config_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_config_free(this_idx1);
  return 0;
}

/* method: add_file_ondisk */
static int Config__add_file_ondisk__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  int priority_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_OK;
  err_idx1 = git_config_add_file_ondisk(this_idx1, path_idx2, priority_idx3);
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: get_int32 */
static int Config__get_int32__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  int32_t out_idx1 = 0;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_config_get_int32(&(out_idx1), this_idx1, name_idx2);
  if(!(GIT_OK != err_idx2)) {
    lua_pushinteger(L, out_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_int32 */
static int Config__set_int32__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  int32_t value_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_OK;
  err_idx1 = git_config_set_int32(this_idx1, name_idx2, value_idx3);
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: get_int64 */
static int Config__get_int64__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  int64_t out_idx1 = 0;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_config_get_int64(&(out_idx1), this_idx1, name_idx2);
  if(!(GIT_OK != err_idx2)) {
    lua_pushinteger(L, out_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_int64 */
static int Config__set_int64__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  int64_t value_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_OK;
  err_idx1 = git_config_set_int64(this_idx1, name_idx2, value_idx3);
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: get_bool */
static int Config__get_bool__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  bool out_idx1 = 0;
  GitError err_idx2 = GIT_OK;
  int out_int_idx3 = 0;
  err_idx2 = git_config_get_bool(&(out_int_idx3), this_idx1, name_idx2);
	out_idx1 = out_int_idx3;

  if(!(GIT_OK != err_idx2)) {
    lua_pushboolean(L, out_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_bool */
static int Config__set_bool__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  bool value_idx2 = lua_toboolean(L,2);
  size_t name_len_idx3;
  const char * name_idx3 = luaL_checklstring(L,3,&(name_len_idx3));
  GitError err_idx1 = GIT_OK;
  int value_int_idx2 = 0;
	value_int_idx2 = value_idx2 ? 1 : 0;

  err_idx1 = git_config_set_bool(this_idx1, name_idx3, value_int_idx2);
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: get_string */
static int Config__get_string__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  const char * out_idx1 = NULL;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_config_get_string(&(out_idx1), this_idx1, name_idx2);
  if(!(GIT_OK != err_idx2)) {
    lua_pushstring(L, out_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_string */
static int Config__set_string__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  size_t value_len_idx3;
  const char * value_idx3 = luaL_checklstring(L,3,&(value_len_idx3));
  GitError err_idx1 = GIT_OK;
  err_idx1 = git_config_set_string(this_idx1, name_idx2, value_idx3);
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: delete */
static int Config__delete__meth(lua_State *L) {
  Config * this_idx1 = obj_type_Config_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  GitError err_idx1 = GIT_OK;
  err_idx1 = git_config_delete(this_idx1, name_idx2);
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: free */
static int OdbObject__free__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  OdbObject * this_idx1 = obj_type_OdbObject_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_odb_object_free(this_idx1);
  return 0;
}

/* method: id */
static int OdbObject__id__meth(lua_State *L) {
  OdbObject * this_idx1 = obj_type_OdbObject_check(L,1);
  OID id_idx1;
  id_idx1 = *git_odb_object_id(this_idx1);
  obj_type_OID_push(L, id_idx1);
  return 1;
}

/* method: data */
static int OdbObject__data__meth(lua_State *L) {
  OdbObject * this_idx1 = obj_type_OdbObject_check(L,1);
  size_t data_len_idx1 = 0;
  const char * data_idx1 = NULL;
  data_idx1 = git_odb_object_data(this_idx1);
  data_len_idx1 = git_odb_object_size(this_idx1);
  if(data_idx1 == NULL) lua_pushnil(L);  else lua_pushlstring(L, data_idx1,data_len_idx1);
  return 1;
}

/* method: size */
static int OdbObject__size__meth(lua_State *L) {
  OdbObject * this_idx1 = obj_type_OdbObject_check(L,1);
  size_t rc_git_odb_object_size_idx1 = 0;
  rc_git_odb_object_size_idx1 = git_odb_object_size(this_idx1);
  lua_pushinteger(L, rc_git_odb_object_size_idx1);
  return 1;
}

/* method: type */
static int OdbObject__type__meth(lua_State *L) {
  OdbObject * this_idx1 = obj_type_OdbObject_check(L,1);
  git_otype otype_idx1;
  const char * type_idx2 = NULL;
  otype_idx1 = git_odb_object_type(this_idx1);
  type_idx2 = git_object_type2string(otype_idx1);
  lua_pushstring(L, type_idx2);
  return 1;
}

/* method: hex */
static int OID__hex__meth(lua_State *L) {
  size_t str_len_idx1;
  const char * str_idx1 = luaL_checklstring(L,1,&(str_len_idx1));
  OID this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_oid_fromstrn(&(this_idx1), str_idx1, str_len_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_OID_push(L, this_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: raw */
static int OID__raw__meth(lua_State *L) {
  size_t raw_len_idx1;
  const unsigned char * raw_idx1 = (unsigned char *)luaL_checklstring(L,1,&(raw_len_idx1));
  OID this_idx1;
		if(raw_len_idx1 < GIT_OID_RAWSZ) {
			lua_pushnil(L);
			lua_pushliteral(L, "Invalid RAW OID");
			return 2;
		}
		
  git_oid_fromraw(&(this_idx1), raw_idx1);
  obj_type_OID_push(L, this_idx1);
  return 1;
}

/* method: pathfmt */
static int OID__pathfmt__meth(lua_State *L) {
  OID this_idx1 = obj_type_OID_check(L,1);
  const char * ret_idx1 = NULL;
	char buf[GIT_OID_HEXSZ+1+1];
  git_oid_pathfmt(buf, &(this_idx1));
	buf[GIT_OID_HEXSZ] = 0;
	ret_idx1 = buf;

  lua_pushstring(L, ret_idx1);
  return 1;
}

/* method: fmt */
static int OID__fmt__meth(lua_State *L) {
  OID this_idx1 = obj_type_OID_check(L,1);
  const char * ret_idx1 = NULL;
	char buf[GIT_OID_HEXSZ+1];
  git_oid_fmt(buf, &(this_idx1));
	buf[GIT_OID_HEXSZ] = 0;
	ret_idx1 = buf;

  lua_pushstring(L, ret_idx1);
  return 1;
}

/* method: __tostring */
static int OID____str____meth(lua_State *L) {
  OID this_idx1 = obj_type_OID_check(L,1);
  const char * ret_idx1 = NULL;
	char buf[GIT_OID_HEXSZ+1];
  git_oid_fmt(buf, &(this_idx1));
	buf[GIT_OID_HEXSZ] = 0;
	ret_idx1 = buf;

  lua_pushstring(L, ret_idx1);
  return 1;
}

/* method: __eq */
static int OID____eq____meth(lua_State *L) {
  OID this_idx1 = obj_type_OID_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int ret_idx1 = 0;
  ret_idx1 = git_oid_cmp(&(this_idx1), &(id_idx2));
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: new */
static int OID_Shorten__new__meth(lua_State *L) {
  size_t min_length_idx1 = luaL_checkinteger(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  OID_Shorten * this_idx1;
  this_idx1 = git_oid_shorten_new(min_length_idx1);
  obj_type_OID_Shorten_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: _priv */
static int OID_Shorten__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  OID_Shorten * this_idx1 = obj_type_OID_Shorten_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_oid_shorten_free(this_idx1);
  return 0;
}

/* method: add */
static int OID_Shorten__add__meth(lua_State *L) {
  OID_Shorten * this_idx1 = obj_type_OID_Shorten_check(L,1);
  size_t text_oid_len_idx2;
  const char * text_oid_idx2 = luaL_checklstring(L,2,&(text_oid_len_idx2));
  GitError rc_idx1 = GIT_OK;
  rc_idx1 = git_oid_shorten_add(this_idx1, text_oid_idx2);
		if(rc_idx1 >= 0) {
			lua_pushinteger(L, rc_idx1);
			return 1;
		}
		
  /* check for error. */
  if((GIT_OK != rc_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: new */
static int ODB__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  ODB * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_odb_new(&(this_idx1));
  if(!(GIT_OK != err_idx2)) {
    obj_type_ODB_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: open */
static int ODB__open__meth(lua_State *L) {
  size_t object_dir_len_idx1;
  const char * object_dir_idx1 = luaL_checklstring(L,1,&(object_dir_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  ODB * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_odb_open(&(this_idx1), object_dir_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_ODB_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: free */
static int ODB__free__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  ODB * this_idx1 = obj_type_ODB_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_odb_free(this_idx1);
  return 0;
}

/* method: add_backend */
static int ODB__add_backend__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  ODBBackend * backend_idx2 = obj_type_ODBBackend_check(L,2);
  int priority_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_OK;
	err_idx1 = git_odb_add_backend(this_idx1, &(backend_idx2->backend), priority_idx3);
	ODBBackend_ref(backend_idx2);

  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: add_alternate */
static int ODB__add_alternate__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  ODBBackend * backend_idx2 = obj_type_ODBBackend_check(L,2);
  int priority_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_OK;
	err_idx1 = git_odb_add_alternate(this_idx1, &(backend_idx2->backend), priority_idx3);
	ODBBackend_ref(backend_idx2);

  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: read */
static int ODB__read__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int out_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  OdbObject * out_idx1;
  GitError rc_git_odb_read_idx2 = GIT_OK;
  rc_git_odb_read_idx2 = git_odb_read(&(out_idx1), this_idx1, &(id_idx2));
  if(!(GIT_OK != rc_git_odb_read_idx2)) {
    obj_type_OdbObject_push(L, out_idx1, out_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_odb_read_idx2);
  return 2;
}

/* method: read_prefix */
static int ODB__read_prefix__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  OID short_id_idx2 = obj_type_OID_check(L,2);
  unsigned int len_idx3 = luaL_checkinteger(L,3);
  int out_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  OdbObject * out_idx1;
  GitError rc_git_odb_read_prefix_idx2 = GIT_OK;
  rc_git_odb_read_prefix_idx2 = git_odb_read_prefix(&(out_idx1), this_idx1, &(short_id_idx2), len_idx3);
  if(!(GIT_OK != rc_git_odb_read_prefix_idx2)) {
    obj_type_OdbObject_push(L, out_idx1, out_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_odb_read_prefix_idx2);
  return 2;
}

/* method: read_header */
static int ODB__read_header__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  size_t len_p_idx1 = 0;
  const char * type_idx2 = NULL;
  GitError err_idx3 = GIT_OK;
  git_otype otype_idx4;
  err_idx3 = git_odb_read_header(&(len_p_idx1), &(otype_idx4), this_idx1, &(id_idx2));
  type_idx2 = git_object_type2string(otype_idx4);
  if(!(GIT_OK != err_idx3)) {
    lua_pushinteger(L, len_p_idx1);
  } else {
    lua_pushnil(L);
  }
  if(!(GIT_OK != err_idx3)) {
    lua_pushstring(L, type_idx2);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx3);
  return 3;
}

/* method: exists */
static int ODB__exists__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  GitError err_idx1 = GIT_OK;
  err_idx1 = git_odb_exists(this_idx1, &(id_idx2));
  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: write */
static int ODB__write__meth(lua_State *L) {
  ODB * this_idx1 = obj_type_ODB_check(L,1);
  size_t data_len_idx2;
  const char * data_idx2 = luaL_checklstring(L,2,&(data_len_idx2));
  size_t type_len_idx3;
  const char * type_idx3 = luaL_checklstring(L,3,&(type_len_idx3));
  OID id_idx1;
  GitError rc_git_odb_write_idx2 = GIT_OK;
  git_otype otype_idx3;
  otype_idx3 = git_object_string2type(type_idx3);
  rc_git_odb_write_idx2 = git_odb_write(&(id_idx1), this_idx1, data_idx2, data_len_idx2, otype_idx3);
  if(!(GIT_OK != rc_git_odb_write_idx2)) {
    obj_type_OID_push(L, id_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_odb_write_idx2);
  return 2;
}

/* method: hash */
static int ODB__hash__func(lua_State *L) {
  size_t data_len_idx1;
  const char * data_idx1 = luaL_checklstring(L,1,&(data_len_idx1));
  git_otype otype_idx2 = luaL_checkinteger(L,2);
  OID id_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_odb_hash(&(id_idx1), data_idx1, data_len_idx1, otype_idx2);
  if(!(GIT_OK != err_idx2)) {
    obj_type_OID_push(L, id_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: hashfile */
static int ODB__hashfile__func(lua_State *L) {
  size_t path_len_idx1;
  const char * path_idx1 = luaL_checklstring(L,1,&(path_len_idx1));
  git_otype otype_idx2 = luaL_checkinteger(L,2);
  OID id_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_odb_hashfile(&(id_idx1), path_idx1, otype_idx2);
  if(!(GIT_OK != err_idx2)) {
    obj_type_OID_push(L, id_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: new */
static int ODBBackend__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  ODBBackend * this_idx1;
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 1);
	/* create backend object. */
	this_idx1 = calloc(1, sizeof(ODBBackend));
	this_idx1->ref_count = 1;
	this_idx1->L = L;
	/* get each callback from table. */
#define REF_CB(_name) \
	lua_getfield(L, 1, "on_" #_name); \
	this_idx1->_name = luaL_ref(L, LUA_REGISTRYINDEX); \
	this_idx1->backend._name = odb_backend_ ## _name ## _cb;

	REF_CB(read)
	REF_CB(read_prefix)
	REF_CB(read_header)
	REF_CB(write)
	REF_CB(exists)
	REF_CB(free)
#undef REF_CB

  obj_type_ODBBackend_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: _priv */
static int ODBBackend__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  ODBBackend * this_idx1 = obj_type_ODBBackend_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
	ODBBackend_unref(this_idx1);

  return 0;
}

/* method: bare */
static int Index__bare__meth(lua_State *L) {
  size_t index_path_len_idx1;
  const char * index_path_idx1 = luaL_checklstring(L,1,&(index_path_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Index * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_index_open(&(this_idx1), index_path_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Index_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: _priv */
static int Index__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Index * this_idx1 = obj_type_Index_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_index_free(this_idx1);
  return 0;
}

/* method: clear */
static int Index__clear__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  git_index_clear(this_idx1);
  return 0;
}

/* method: read */
static int Index__read__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  GitError rc_git_index_read_idx1 = GIT_OK;
  rc_git_index_read_idx1 = git_index_read(this_idx1);
  /* check for error. */
  if((GIT_OK != rc_git_index_read_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_read_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: write */
static int Index__write__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  GitError rc_git_index_write_idx1 = GIT_OK;
  rc_git_index_write_idx1 = git_index_write(this_idx1);
  /* check for error. */
  if((GIT_OK != rc_git_index_write_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_write_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: find */
static int Index__find__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  int rc_git_index_find_idx1 = 0;
  rc_git_index_find_idx1 = git_index_find(this_idx1, path_idx2);
  lua_pushinteger(L, rc_git_index_find_idx1);
  return 1;
}

/* method: uniq */
static int Index__uniq__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  git_index_uniq(this_idx1);
  return 0;
}

/* method: add */
static int Index__add__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  int stage_idx3 = luaL_checkinteger(L,3);
  GitError rc_git_index_add_idx1 = GIT_OK;
  rc_git_index_add_idx1 = git_index_add(this_idx1, path_idx2, stage_idx3);
  /* check for error. */
  if((GIT_OK != rc_git_index_add_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_add_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: add2 */
static int Index__add2__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  IndexEntry * source_entry_idx2 = obj_type_IndexEntry_check(L,2);
  GitError rc_git_index_add2_idx1 = GIT_OK;
  rc_git_index_add2_idx1 = git_index_add2(this_idx1, source_entry_idx2);
  /* check for error. */
  if((GIT_OK != rc_git_index_add2_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_add2_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: append */
static int Index__append__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  int stage_idx3 = luaL_checkinteger(L,3);
  GitError rc_git_index_append_idx1 = GIT_OK;
  rc_git_index_append_idx1 = git_index_append(this_idx1, path_idx2, stage_idx3);
  /* check for error. */
  if((GIT_OK != rc_git_index_append_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_append_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: append2 */
static int Index__append2__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  IndexEntry * source_entry_idx2 = obj_type_IndexEntry_check(L,2);
  GitError rc_git_index_append2_idx1 = GIT_OK;
  rc_git_index_append2_idx1 = git_index_append2(this_idx1, source_entry_idx2);
  /* check for error. */
  if((GIT_OK != rc_git_index_append2_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_append2_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: remove */
static int Index__remove__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  int position_idx2 = luaL_checkinteger(L,2);
  GitError rc_git_index_remove_idx1 = GIT_OK;
  rc_git_index_remove_idx1 = git_index_remove(this_idx1, position_idx2);
  /* check for error. */
  if((GIT_OK != rc_git_index_remove_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_remove_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: get */
static int Index__get__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  int n_idx2 = luaL_checkinteger(L,2);
  IndexEntry * rc_git_index_get_idx1;
  rc_git_index_get_idx1 = git_index_get(this_idx1, n_idx2);
  obj_type_IndexEntry_push(L, rc_git_index_get_idx1, 0);
  return 1;
}

/* method: entrycount */
static int Index__entrycount__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  unsigned int rc_git_index_entrycount_idx1 = 0;
  rc_git_index_entrycount_idx1 = git_index_entrycount(this_idx1);
  lua_pushinteger(L, rc_git_index_entrycount_idx1);
  return 1;
}

/* method: entrycount_unmerged */
static int Index__entrycount_unmerged__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  unsigned int rc_git_index_entrycount_unmerged_idx1 = 0;
  rc_git_index_entrycount_unmerged_idx1 = git_index_entrycount_unmerged(this_idx1);
  lua_pushinteger(L, rc_git_index_entrycount_unmerged_idx1);
  return 1;
}

/* method: get_unmerged_bypath */
static int Index__get_unmerged_bypath__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  const IndexEntryUnmerged * rc_git_index_get_unmerged_bypath_idx1;
  rc_git_index_get_unmerged_bypath_idx1 = git_index_get_unmerged_bypath(this_idx1, path_idx2);
  obj_type_IndexEntryUnmerged_push(L, rc_git_index_get_unmerged_bypath_idx1, 0);
  return 1;
}

/* method: get_unmerged_byindex */
static int Index__get_unmerged_byindex__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  int n_idx2 = luaL_checkinteger(L,2);
  const IndexEntryUnmerged * rc_git_index_get_unmerged_byindex_idx1;
  rc_git_index_get_unmerged_byindex_idx1 = git_index_get_unmerged_byindex(this_idx1, n_idx2);
  obj_type_IndexEntryUnmerged_push(L, rc_git_index_get_unmerged_byindex_idx1, 0);
  return 1;
}

/* method: read_tree */
static int Index__read_tree__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  Tree * tree_idx2 = obj_type_Tree_check(L,2);
  GitError rc_git_index_read_tree_idx1 = GIT_OK;
  rc_git_index_read_tree_idx1 = git_index_read_tree(this_idx1, tree_idx2);
  /* check for error. */
  if((GIT_OK != rc_git_index_read_tree_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_index_read_tree_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: new */
static int IndexEntry__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  IndexEntry * this_idx1;
	this_idx1 = calloc(1, sizeof(IndexEntry));

  obj_type_IndexEntry_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: _priv */
static int IndexEntry__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  IndexEntry * this_idx1 = obj_type_IndexEntry_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
	if(this_idx1->path != NULL) {
		free(this_idx1->path);
	}
	free(this_idx1);

  return 0;
}

/* method: stage */
static int IndexEntry__stage__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  int rc_git_index_entry_stage_idx1 = 0;
  rc_git_index_entry_stage_idx1 = git_index_entry_stage(this_idx1);
  lua_pushinteger(L, rc_git_index_entry_stage_idx1);
  return 1;
}

/* method: ctime */
static int IndexEntry__ctime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  git_time_t secs_idx1 = 0;
  unsigned int nanosecs_idx2 = 0;
	secs_idx1 = this_idx1->ctime.seconds;
	nanosecs_idx2 = this_idx1->ctime.nanoseconds;

  lua_pushinteger(L, secs_idx1);
  lua_pushinteger(L, nanosecs_idx2);
  return 2;
}

/* method: set_ctime */
static int IndexEntry__set_ctime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  git_time_t secs_idx2 = luaL_checkinteger(L,2);
  unsigned int nanosecs_idx3 = luaL_checkinteger(L,3);
	this_idx1->ctime.seconds = secs_idx2;
	this_idx1->ctime.nanoseconds = nanosecs_idx3;

  return 0;
}

/* method: mtime */
static int IndexEntry__mtime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  git_time_t secs_idx1 = 0;
  unsigned int nanosecs_idx2 = 0;
	secs_idx1 = this_idx1->mtime.seconds;
	nanosecs_idx2 = this_idx1->mtime.nanoseconds;

  lua_pushinteger(L, secs_idx1);
  lua_pushinteger(L, nanosecs_idx2);
  return 2;
}

/* method: set_mtime */
static int IndexEntry__set_mtime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  git_time_t secs_idx2 = luaL_checkinteger(L,2);
  unsigned int nanosecs_idx3 = luaL_checkinteger(L,3);
	this_idx1->mtime.seconds = secs_idx2;
	this_idx1->mtime.nanoseconds = nanosecs_idx3;

  return 0;
}

/* method: path */
static int IndexEntry__path__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  const char * ret_idx1 = NULL;
ret_idx1 = this_idx1->path;
  lua_pushstring(L, ret_idx1);
  return 1;
}

/* method: set_path */
static int IndexEntry__set_path__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  size_t val_len_idx2;
  const char * val_idx2 = luaL_checklstring(L,2,&(val_len_idx2));
	if(this_idx1->path != NULL) {
		free(this_idx1->path);
	}
	this_idx1->path = malloc(val_len_idx2);
	strncpy(this_idx1->path, val_idx2, val_len_idx2);
	this_idx1->path[val_len_idx2] = 0;

  return 0;
}

/* method: dev */
static int IndexEntry__dev__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->dev;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: ino */
static int IndexEntry__ino__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->ino;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: mode */
static int IndexEntry__mode__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->mode;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: uid */
static int IndexEntry__uid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->uid;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: gid */
static int IndexEntry__gid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->gid;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: file_size */
static int IndexEntry__file_size__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  off_t field_idx1 = 0;
	field_idx1 = this_idx1->file_size;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: oid */
static int IndexEntry__oid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  OID field_idx1;
	field_idx1 = this_idx1->oid;

  obj_type_OID_push(L, field_idx1);
  return 1;
}

/* method: flags */
static int IndexEntry__flags__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->flags;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: flags_extended */
static int IndexEntry__flags_extended__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int field_idx1 = 0;
	field_idx1 = this_idx1->flags_extended;

  lua_pushinteger(L, field_idx1);
  return 1;
}

/* method: mode */
static int IndexEntryUnmerged__mode__meth(lua_State *L) {
  IndexEntryUnmerged * this_idx1 = obj_type_IndexEntryUnmerged_check(L,1);
  int idx_idx2 = luaL_checkinteger(L,2);
  unsigned int mode_idx1 = 0;
	if(idx_idx2 < 0 || idx_idx2 >=3) {
		return luaL_argerror(L, 2, "Index out-of-bounds (0-2)");
	}
	mode_idx1 = this_idx1->mode[idx_idx2];

  lua_pushinteger(L, mode_idx1);
  return 1;
}

/* method: oid */
static int IndexEntryUnmerged__oid__meth(lua_State *L) {
  IndexEntryUnmerged * this_idx1 = obj_type_IndexEntryUnmerged_check(L,1);
  int idx_idx2 = luaL_checkinteger(L,2);
  OID oid_idx1;
	if(idx_idx2 < 0 || idx_idx2 >=3) {
		return luaL_argerror(L, 2, "Index out-of-bounds (0-2)");
	}
	oid_idx1 = this_idx1->oid[idx_idx2];

  obj_type_OID_push(L, oid_idx1);
  return 1;
}

/* method: path */
static int IndexEntryUnmerged__path__meth(lua_State *L) {
  IndexEntryUnmerged * this_idx1 = obj_type_IndexEntryUnmerged_check(L,1);
  const char * ret_idx1 = NULL;
ret_idx1 = this_idx1->path;
  lua_pushstring(L, ret_idx1);
  return 1;
}

/* method: free */
static int Object__free__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Object * this_idx1 = obj_type_Object_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_object_free(this_idx1);
  return 0;
}

/* method: id */
static int Object__id__meth(lua_State *L) {
  Object * this_idx1 = obj_type_Object_check(L,1);
  OID id_idx1;
  id_idx1 = *git_object_id(this_idx1);
  obj_type_OID_push(L, id_idx1);
  return 1;
}

/* method: type */
static int Object__type__meth(lua_State *L) {
  Object * this_idx1 = obj_type_Object_check(L,1);
  git_otype otype_idx1;
  const char * type_idx2 = NULL;
  otype_idx1 = git_object_type(this_idx1);
  type_idx2 = git_object_type2string(otype_idx1);
  lua_pushstring(L, type_idx2);
  return 1;
}

/* method: owner */
static int Object__owner__meth(lua_State *L) {
  Object * this_idx1 = obj_type_Object_check(L,1);
  Repository * rc_git_object_owner_idx1;
  rc_git_object_owner_idx1 = git_object_owner(this_idx1);
  obj_type_Repository_push(L, rc_git_object_owner_idx1, 0);
  return 1;
}

/* method: type2string */
static int Object__type2string__func(lua_State *L) {
  git_otype otype_idx1 = luaL_checkinteger(L,1);
  const char * rc_git_object_type2string_idx1 = NULL;
  rc_git_object_type2string_idx1 = git_object_type2string(otype_idx1);
  lua_pushstring(L, rc_git_object_type2string_idx1);
  return 1;
}

/* method: string2type */
static int Object__string2type__func(lua_State *L) {
  size_t str_len_idx1;
  const char * str_idx1 = luaL_checklstring(L,1,&(str_len_idx1));
  git_otype rc_git_object_string2type_idx1;
  rc_git_object_string2type_idx1 = git_object_string2type(str_idx1);
  lua_pushinteger(L, rc_git_object_string2type_idx1);
  return 1;
}

static void dyn_caster_Object(void **obj, obj_type **type) {
  Object * base_obj = (Object *)*obj;
  switch(git_object_type(base_obj)) {
  case GIT_OBJ_COMMIT:
    *type = &(obj_type_Commit);
    break;
  case GIT_OBJ_BLOB:
    *type = &(obj_type_Blob);
    break;
  case GIT_OBJ_TREE:
    *type = &(obj_type_Tree);
    break;
  case GIT_OBJ_TAG:
    *type = &(obj_type_Tag);
    break;
  default:
    break;
  }
}

/* method: lookup */
static int Blob__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Blob * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_blob_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_OK != err_idx2)) {
    obj_type_Blob_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: fromfile */
static int Blob__fromfile__func(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  OID written_id_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_blob_create_fromfile(&(written_id_idx1), repo_idx1, path_idx2);
  if(!(GIT_OK != err_idx2)) {
    obj_type_OID_push(L, written_id_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: frombuffer */
static int Blob__frombuffer__func(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  size_t buffer_len_idx2;
  const char * buffer_idx2 = luaL_checklstring(L,2,&(buffer_len_idx2));
  OID written_id_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_blob_create_frombuffer(&(written_id_idx1), repo_idx1, buffer_idx2, buffer_len_idx2);
  if(!(GIT_OK != err_idx2)) {
    obj_type_OID_push(L, written_id_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: rawcontent */
static int Blob__rawcontent__meth(lua_State *L) {
  Blob * this_idx1 = obj_type_Blob_check(L,1);
  size_t buff_len_idx1 = 0;
  const char * buff_idx1 = NULL;
  buff_idx1 = git_blob_rawcontent(this_idx1);
  buff_len_idx1 = git_blob_rawsize(this_idx1);
  if(buff_idx1 == NULL) lua_pushnil(L);  else lua_pushlstring(L, buff_idx1,buff_len_idx1);
  return 1;
}

/* method: rawsize */
static int Blob__rawsize__meth(lua_State *L) {
  Blob * this_idx1 = obj_type_Blob_check(L,1);
  int rc_git_blob_rawsize_idx1 = 0;
  rc_git_blob_rawsize_idx1 = git_blob_rawsize(this_idx1);
  lua_pushinteger(L, rc_git_blob_rawsize_idx1);
  return 1;
}

/* method: new */
static int Signature__new__meth(lua_State *L) {
  size_t name_len_idx1;
  const char * name_idx1 = luaL_checklstring(L,1,&(name_len_idx1));
  size_t email_len_idx2;
  const char * email_idx2 = luaL_checklstring(L,2,&(email_len_idx2));
  git_time_t time_idx3 = luaL_checkinteger(L,3);
  int offset_idx4 = luaL_checkinteger(L,4);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Signature * this_idx1;
  GitError rc_git_signature_new_idx2 = GIT_OK;
  rc_git_signature_new_idx2 = git_signature_new(&(this_idx1), name_idx1, email_idx2, time_idx3, offset_idx4);
  if(!(GIT_OK != rc_git_signature_new_idx2)) {
    obj_type_Signature_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_signature_new_idx2);
  return 2;
}

/* method: now */
static int Signature__now__meth(lua_State *L) {
  size_t name_len_idx1;
  const char * name_idx1 = luaL_checklstring(L,1,&(name_len_idx1));
  size_t email_len_idx2;
  const char * email_idx2 = luaL_checklstring(L,2,&(email_len_idx2));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Signature * this_idx1;
  GitError rc_git_signature_now_idx2 = GIT_OK;
  rc_git_signature_now_idx2 = git_signature_now(&(this_idx1), name_idx1, email_idx2);
  if(!(GIT_OK != rc_git_signature_now_idx2)) {
    obj_type_Signature_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_signature_now_idx2);
  return 2;
}

/* method: _priv */
static int Signature__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Signature * this_idx1 = obj_type_Signature_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_signature_free(this_idx1);
  return 0;
}

/* method: name */
static int Signature__name__meth(lua_State *L) {
  Signature * this_idx1 = obj_type_Signature_check(L,1);
  const char * name_idx1 = NULL;
name_idx1 = this_idx1->name;
  lua_pushstring(L, name_idx1);
  return 1;
}

/* method: email */
static int Signature__email__meth(lua_State *L) {
  Signature * this_idx1 = obj_type_Signature_check(L,1);
  const char * email_idx1 = NULL;
email_idx1 = this_idx1->email;
  lua_pushstring(L, email_idx1);
  return 1;
}

/* method: when */
static int Signature__when__meth(lua_State *L) {
  Signature * this_idx1 = obj_type_Signature_check(L,1);
  git_time_t time_idx1 = 0;
  int offset_idx2 = 0;
time_idx1 = this_idx1->when.time; offset_idx2 = this_idx1->when.offset;
  lua_pushinteger(L, time_idx1);
  lua_pushinteger(L, offset_idx2);
  return 2;
}

/* method: lookup */
static int Commit__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Commit * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_commit_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_OK != err_idx2)) {
    obj_type_Commit_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: create */
static int Commit__create__func(lua_State *L) {
  OID oid_idx1 = obj_type_OID_check(L,1);
  Repository * repo_idx2 = obj_type_Repository_check(L,2);
  size_t update_ref_len_idx3;
  const char * update_ref_idx3 = luaL_checklstring(L,3,&(update_ref_len_idx3));
  Signature * author_idx4 = obj_type_Signature_check(L,4);
  Signature * committer_idx5 = obj_type_Signature_check(L,5);
  size_t message_encoding_len_idx6;
  const char * message_encoding_idx6 = luaL_checklstring(L,6,&(message_encoding_len_idx6));
  size_t message_len_idx7;
  const char * message_idx7 = luaL_checklstring(L,7,&(message_len_idx7));
  Tree * tree_idx8 = obj_type_Tree_check(L,8);
  Commit * parent_idx9 = obj_type_Commit_check(L,9);
  GitError err_idx1 = GIT_OK;
	int parent_count = 0;
	const git_commit **parents;
	int n;

	/* count parents. */
	parent_count = lua_gettop(L) - 9 + 1;
	/* valid parents.  The first parent commit is already validated. */
	for(n = 1; n < parent_count; n++) {
		obj_type_Commit_check(L, 9 + n);
	}
	/* now it is safe to allocate oid array. */
	parents = malloc(parent_count * sizeof(git_commit *));

	/* copy oids from all parents into oid array. */
	parents[0] = parent_idx9;
	for(n = 1; n < parent_count; n++) {
		parents[n] = obj_type_Commit_check(L, 9 + n);
	}

	err_idx1 = git_commit_create(&(oid_idx1), repo_idx2, update_ref_idx3,
		author_idx4, committer_idx5, message_encoding_idx6, message_idx7,
		tree_idx8, parent_count, parents);
	/* free parent oid array. */
	free(parents);

  /* check for error. */
  if((GIT_OK != err_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: id */
static int Commit__id__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  OID id_idx1;
  id_idx1 = *git_commit_id(this_idx1);
  obj_type_OID_push(L, id_idx1);
  return 1;
}

/* method: message_encoding */
static int Commit__message_encoding__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const char * rc_git_commit_message_encoding_idx1 = NULL;
  rc_git_commit_message_encoding_idx1 = git_commit_message_encoding(this_idx1);
  lua_pushstring(L, rc_git_commit_message_encoding_idx1);
  return 1;
}

/* method: message */
static int Commit__message__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const char * rc_git_commit_message_idx1 = NULL;
  rc_git_commit_message_idx1 = git_commit_message(this_idx1);
  lua_pushstring(L, rc_git_commit_message_idx1);
  return 1;
}

/* method: time */
static int Commit__time__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  git_time_t rc_git_commit_time_idx1 = 0;
  rc_git_commit_time_idx1 = git_commit_time(this_idx1);
  lua_pushinteger(L, rc_git_commit_time_idx1);
  return 1;
}

/* method: time_offset */
static int Commit__time_offset__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  int rc_git_commit_time_offset_idx1 = 0;
  rc_git_commit_time_offset_idx1 = git_commit_time_offset(this_idx1);
  lua_pushinteger(L, rc_git_commit_time_offset_idx1);
  return 1;
}

/* method: committer */
static int Commit__committer__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const Signature * rc_git_commit_committer_idx1;
  rc_git_commit_committer_idx1 = git_commit_committer(this_idx1);
  obj_type_Signature_push(L, rc_git_commit_committer_idx1, 0);
  return 1;
}

/* method: author */
static int Commit__author__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const Signature * rc_git_commit_author_idx1;
  rc_git_commit_author_idx1 = git_commit_author(this_idx1);
  obj_type_Signature_push(L, rc_git_commit_author_idx1, 0);
  return 1;
}

/* method: tree */
static int Commit__tree__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  int tree_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tree * tree_idx1;
  GitError rc_git_commit_tree_idx2 = GIT_OK;
  rc_git_commit_tree_idx2 = git_commit_tree(&(tree_idx1), this_idx1);
  if(!(GIT_OK != rc_git_commit_tree_idx2)) {
    obj_type_Tree_push(L, tree_idx1, tree_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_commit_tree_idx2);
  return 2;
}

/* method: parentcount */
static int Commit__parentcount__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  unsigned int rc_git_commit_parentcount_idx1 = 0;
  rc_git_commit_parentcount_idx1 = git_commit_parentcount(this_idx1);
  lua_pushinteger(L, rc_git_commit_parentcount_idx1);
  return 1;
}

/* method: parent */
static int Commit__parent__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  unsigned int n_idx2 = luaL_checkinteger(L,2);
  Commit * parent_idx1;
  GitError rc_git_commit_parent_idx2 = GIT_OK;
  rc_git_commit_parent_idx2 = git_commit_parent(&(parent_idx1), this_idx1, n_idx2);
  if(!(GIT_OK != rc_git_commit_parent_idx2)) {
    obj_type_Commit_push(L, parent_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_commit_parent_idx2);
  return 2;
}

/* method: lookup */
static int Tree__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tree * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_tree_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_OK != err_idx2)) {
    obj_type_Tree_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: entrycount */
static int Tree__entrycount__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  size_t rc_git_tree_entrycount_idx1 = 0;
  rc_git_tree_entrycount_idx1 = git_tree_entrycount(this_idx1);
  lua_pushinteger(L, rc_git_tree_entrycount_idx1);
  return 1;
}

/* method: entry_byname */
static int Tree__entry_byname__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  size_t filename_len_idx2;
  const char * filename_idx2 = luaL_checklstring(L,2,&(filename_len_idx2));
  const TreeEntry * rc_git_tree_entry_byname_idx1;
  rc_git_tree_entry_byname_idx1 = git_tree_entry_byname(this_idx1, filename_idx2);
  obj_type_TreeEntry_push(L, rc_git_tree_entry_byname_idx1, 0);
  return 1;
}

/* method: entry_byindex */
static int Tree__entry_byindex__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  int index_idx2 = luaL_checkinteger(L,2);
  const TreeEntry * rc_git_tree_entry_byindex_idx1;
  rc_git_tree_entry_byindex_idx1 = git_tree_entry_byindex(this_idx1, index_idx2);
  obj_type_TreeEntry_push(L, rc_git_tree_entry_byindex_idx1, 0);
  return 1;
}

/* method: name */
static int TreeEntry__name__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  const char * rc_git_tree_entry_name_idx1 = NULL;
  rc_git_tree_entry_name_idx1 = git_tree_entry_name(this_idx1);
  lua_pushstring(L, rc_git_tree_entry_name_idx1);
  return 1;
}

/* method: attributes */
static int TreeEntry__attributes__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  unsigned int rc_git_tree_entry_attributes_idx1 = 0;
  rc_git_tree_entry_attributes_idx1 = git_tree_entry_attributes(this_idx1);
  lua_pushinteger(L, rc_git_tree_entry_attributes_idx1);
  return 1;
}

/* method: id */
static int TreeEntry__id__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  OID id_idx1;
id_idx1 = *(git_tree_entry_id(this_idx1));
  obj_type_OID_push(L, id_idx1);
  return 1;
}

/* method: object */
static int TreeEntry__object__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  Repository * repo_idx2 = obj_type_Repository_check(L,2);
  int obj_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Object * obj_idx1;
  GitError rc_git_tree_entry_to_object_idx2 = GIT_OK;
  rc_git_tree_entry_to_object_idx2 = git_tree_entry_to_object(&(obj_idx1), repo_idx2, this_idx1);
  if(!(GIT_OK != rc_git_tree_entry_to_object_idx2)) {
    obj_type_Object_push(L, obj_idx1, obj_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_tree_entry_to_object_idx2);
  return 2;
}

/* method: lookup */
static int Tag__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tag * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_tag_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_OK != err_idx2)) {
    obj_type_Tag_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: target */
static int Tag__target__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  Object * out_idx1;
  GitError rc_git_tag_target_idx2 = GIT_OK;
  rc_git_tag_target_idx2 = git_tag_target(&(out_idx1), this_idx1);
  if(!(GIT_OK != rc_git_tag_target_idx2)) {
    obj_type_Object_push(L, out_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_tag_target_idx2);
  return 2;
}

/* method: name */
static int Tag__name__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const char * rc_git_tag_name_idx1 = NULL;
  rc_git_tag_name_idx1 = git_tag_name(this_idx1);
  lua_pushstring(L, rc_git_tag_name_idx1);
  return 1;
}

/* method: tagger */
static int Tag__tagger__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const Signature * rc_git_tag_tagger_idx1;
  rc_git_tag_tagger_idx1 = git_tag_tagger(this_idx1);
  obj_type_Signature_push(L, rc_git_tag_tagger_idx1, 0);
  return 1;
}

/* method: message */
static int Tag__message__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const char * rc_git_tag_message_idx1 = NULL;
  rc_git_tag_message_idx1 = git_tag_message(this_idx1);
  lua_pushstring(L, rc_git_tag_message_idx1);
  return 1;
}

/* method: new */
static int RevWalk__new__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  RevWalk * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_revwalk_new(&(this_idx1), repo_idx1);
  if(!(GIT_OK != err_idx2)) {
    obj_type_RevWalk_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: close */
static int RevWalk__close__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  RevWalk * this_idx1 = obj_type_RevWalk_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_revwalk_free(this_idx1);
  return 0;
}

/* method: reset */
static int RevWalk__reset__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  git_revwalk_reset(this_idx1);
  return 0;
}

/* method: push */
static int RevWalk__push__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  GitError rc_git_revwalk_push_idx1 = GIT_OK;
  rc_git_revwalk_push_idx1 = git_revwalk_push(this_idx1, &(id_idx2));
  /* check for error. */
  if((GIT_OK != rc_git_revwalk_push_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_revwalk_push_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: hide */
static int RevWalk__hide__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  GitError rc_git_revwalk_hide_idx1 = GIT_OK;
  rc_git_revwalk_hide_idx1 = git_revwalk_hide(this_idx1, &(id_idx2));
  /* check for error. */
  if((GIT_OK != rc_git_revwalk_hide_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_revwalk_hide_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: next */
static int RevWalk__next__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  OID id_idx1;
  GitError rc_git_revwalk_next_idx2 = GIT_OK;
  rc_git_revwalk_next_idx2 = git_revwalk_next(&(id_idx1), this_idx1);
  if(!(GIT_OK != rc_git_revwalk_next_idx2)) {
    obj_type_OID_push(L, id_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_revwalk_next_idx2);
  return 2;
}

/* method: sorting */
static int RevWalk__sorting__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  unsigned int sort_mode_idx2 = luaL_checkinteger(L,2);
  git_revwalk_sorting(this_idx1, sort_mode_idx2);
  return 0;
}

/* method: repository */
static int RevWalk__repository__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  Repository * rc_git_revwalk_repository_idx1;
  rc_git_revwalk_repository_idx1 = git_revwalk_repository(this_idx1);
  obj_type_Repository_push(L, rc_git_revwalk_repository_idx1, 0);
  return 1;
}

/* method: lookup */
static int Reference__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Reference * this_idx1;
  GitError err_idx2 = GIT_OK;
  err_idx2 = git_reference_lookup(&(this_idx1), repo_idx1, name_idx2);
  if(!(GIT_OK != err_idx2)) {
    obj_type_Reference_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: oid */
static int Reference__oid__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  OID rc_git_reference_oid_idx1;
  rc_git_reference_oid_idx1 = *git_reference_oid(this_idx1);
  obj_type_OID_push(L, rc_git_reference_oid_idx1);
  return 1;
}

/* method: set_oid */
static int Reference__set_oid__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  OID oid_idx2 = obj_type_OID_check(L,2);
  GitError rc_git_reference_set_oid_idx1 = GIT_OK;
  rc_git_reference_set_oid_idx1 = git_reference_set_oid(this_idx1, &(oid_idx2));
  /* check for error. */
  if((GIT_OK != rc_git_reference_set_oid_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_reference_set_oid_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: target */
static int Reference__target__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  const char * rc_git_reference_target_idx1 = NULL;
  rc_git_reference_target_idx1 = git_reference_target(this_idx1);
  lua_pushstring(L, rc_git_reference_target_idx1);
  return 1;
}

/* method: set_target */
static int Reference__set_target__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  size_t target_len_idx2;
  const char * target_idx2 = luaL_checklstring(L,2,&(target_len_idx2));
  GitError rc_git_reference_set_target_idx1 = GIT_OK;
  rc_git_reference_set_target_idx1 = git_reference_set_target(this_idx1, target_idx2);
  /* check for error. */
  if((GIT_OK != rc_git_reference_set_target_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_reference_set_target_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: type */
static int Reference__type__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  git_ref_t rc_git_reference_type_idx1;
  rc_git_reference_type_idx1 = git_reference_type(this_idx1);
  lua_pushinteger(L, rc_git_reference_type_idx1);
  return 1;
}

/* method: name */
static int Reference__name__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  const char * rc_git_reference_name_idx1 = NULL;
  rc_git_reference_name_idx1 = git_reference_name(this_idx1);
  lua_pushstring(L, rc_git_reference_name_idx1);
  return 1;
}

/* method: resolve */
static int Reference__resolve__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  Reference * resolved_ref_idx1;
  GitError rc_git_reference_resolve_idx2 = GIT_OK;
  rc_git_reference_resolve_idx2 = git_reference_resolve(&(resolved_ref_idx1), this_idx1);
  if(!(GIT_OK != rc_git_reference_resolve_idx2)) {
    obj_type_Reference_push(L, resolved_ref_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, rc_git_reference_resolve_idx2);
  return 2;
}

/* method: owner */
static int Reference__owner__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  Repository * rc_git_reference_owner_idx1;
  rc_git_reference_owner_idx1 = git_reference_owner(this_idx1);
  obj_type_Repository_push(L, rc_git_reference_owner_idx1, 0);
  return 1;
}

/* method: rename */
static int Reference__rename__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  size_t new_name_len_idx2;
  const char * new_name_idx2 = luaL_checklstring(L,2,&(new_name_len_idx2));
  bool force_idx3 = lua_toboolean(L,3);
  GitError rc_git_reference_rename_idx1 = GIT_OK;
  rc_git_reference_rename_idx1 = git_reference_rename(this_idx1, new_name_idx2, force_idx3);
  /* check for error. */
  if((GIT_OK != rc_git_reference_rename_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_reference_rename_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: delete */
static int Reference__delete__meth(lua_State *L) {
  Reference * this_idx1 = obj_type_Reference_check(L,1);
  GitError rc_git_reference_delete_idx1 = GIT_OK;
  rc_git_reference_delete_idx1 = git_reference_delete(this_idx1);
  /* check for error. */
  if((GIT_OK != rc_git_reference_delete_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_reference_delete_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: packall */
static int Reference__packall__func(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  GitError rc_git_reference_packall_idx1 = GIT_OK;
  rc_git_reference_packall_idx1 = git_reference_packall(repo_idx1);
  /* check for error. */
  if((GIT_OK != rc_git_reference_packall_idx1)) {
    lua_pushnil(L);
      error_code__GitError__push(L, rc_git_reference_packall_idx1);
  } else {
    lua_pushboolean(L, 1);
    lua_pushnil(L);
  }
  return 2;
}

/* method: list */
static int Reference__list__func(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  unsigned int list_flags_idx2 = luaL_checkinteger(L,2);
  StrArray array_idx1_store;
  StrArray * array_idx1 = &(array_idx1_store);
  GitError err_idx2 = GIT_OK;
	git_strarray tmp_array = { .strings = NULL, .count = 0 };

	/* push this onto stack now, just encase there is a out-of-memory error. */
	array_idx1 = obj_type_StrArray_push(L, &tmp_array);
	err_idx2 = git_reference_list(array_idx1, repo_idx1, list_flags_idx2);
	if(err_idx2 == GIT_OK) {
		return 1; /* array is already on the stack. */
	} else {
		/* there is an error remove the temp array from stack. */
		lua_pop(L, 1);
		array_idx1 = NULL;
	}

  if(!(GIT_OK != err_idx2)) {
    obj_type_StrArray_push(L, array_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}



static const luaL_reg obj_StrArray_pub_funcs[] = {
  {"new", StrArray__new__meth},
  {NULL, NULL}
};

static const luaL_reg obj_StrArray_methods[] = {
  {"free", StrArray__free__meth},
  {"str", StrArray__str__meth},
  {"get_array", StrArray__get_array__meth},
  {"count", StrArray__count__meth},
  {NULL, NULL}
};

static const luaL_reg obj_StrArray_metas[] = {
  {"__gc", StrArray__free__meth},
  {"__tostring", obj_simple_udata_default_tostring},
  {"__eq", obj_simple_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_StrArray_bases[] = {
  {-1, NULL}
};

static const obj_field obj_StrArray_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_StrArray_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Repository_pub_funcs[] = {
  {"open", Repository__open__meth},
  {"init", Repository__init__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Repository_methods[] = {
  {"head", Repository__head__meth},
  {"head_detached", Repository__head_detached__meth},
  {"head_orphan", Repository__head_orphan__meth},
  {"is_empty", Repository__is_empty__meth},
  {"is_bare", Repository__is_bare__meth},
  {"path", Repository__path__meth},
  {"workdir", Repository__workdir__meth},
  {"set_workdir", Repository__set_workdir__meth},
  {"config", Repository__config__meth},
  {"set_config", Repository__set_config__meth},
  {"odb", Repository__odb__meth},
  {"set_odb", Repository__set_odb__meth},
  {"index", Repository__index__meth},
  {"set_index", Repository__set_index__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Repository_metas[] = {
  {"__gc", Repository__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Repository_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Repository_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Repository_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Config_pub_funcs[] = {
  {"new", Config__new__meth},
  {"open", Config__open__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Config_methods[] = {
  {"free", Config__free__meth},
  {"add_file_ondisk", Config__add_file_ondisk__meth},
  {"get_int32", Config__get_int32__meth},
  {"set_int32", Config__set_int32__meth},
  {"get_int64", Config__get_int64__meth},
  {"set_int64", Config__set_int64__meth},
  {"get_bool", Config__get_bool__meth},
  {"set_bool", Config__set_bool__meth},
  {"get_string", Config__get_string__meth},
  {"set_string", Config__set_string__meth},
  {"delete", Config__delete__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Config_metas[] = {
  {"__gc", Config__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Config_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Config_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Config_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_OdbObject_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_reg obj_OdbObject_methods[] = {
  {"free", OdbObject__free__meth},
  {"id", OdbObject__id__meth},
  {"data", OdbObject__data__meth},
  {"size", OdbObject__size__meth},
  {"type", OdbObject__type__meth},
  {NULL, NULL}
};

static const luaL_reg obj_OdbObject_metas[] = {
  {"__gc", OdbObject__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_OdbObject_bases[] = {
  {-1, NULL}
};

static const obj_field obj_OdbObject_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_OdbObject_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_OID_pub_funcs[] = {
  {"hex", OID__hex__meth},
  {"raw", OID__raw__meth},
  {NULL, NULL}
};

static const luaL_reg obj_OID_methods[] = {
  {"pathfmt", OID__pathfmt__meth},
  {"fmt", OID__fmt__meth},
  {NULL, NULL}
};

static const luaL_reg obj_OID_metas[] = {
  {"__tostring", OID____str____meth},
  {"__eq", OID____eq____meth},
  {NULL, NULL}
};

static const obj_base obj_OID_bases[] = {
  {-1, NULL}
};

static const obj_field obj_OID_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_OID_constants[] = {
#ifdef GIT_OID_RAWSZ
  {"RAWSZ", NULL, GIT_OID_RAWSZ, CONST_NUMBER},
#endif
#ifdef GIT_OID_MINPREFIXLEN
  {"MINPREFIXLEN", NULL, GIT_OID_MINPREFIXLEN, CONST_NUMBER},
#endif
#ifdef GIT_OID_HEXSZ
  {"HEXSZ", NULL, GIT_OID_HEXSZ, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_OID_Shorten_pub_funcs[] = {
  {"new", OID_Shorten__new__meth},
  {NULL, NULL}
};

static const luaL_reg obj_OID_Shorten_methods[] = {
  {"add", OID_Shorten__add__meth},
  {NULL, NULL}
};

static const luaL_reg obj_OID_Shorten_metas[] = {
  {"__gc", OID_Shorten__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_OID_Shorten_bases[] = {
  {-1, NULL}
};

static const obj_field obj_OID_Shorten_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_OID_Shorten_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_ODB_pub_funcs[] = {
  {"new", ODB__new__meth},
  {"open", ODB__open__meth},
  {"hash", ODB__hash__func},
  {"hashfile", ODB__hashfile__func},
  {NULL, NULL}
};

static const luaL_reg obj_ODB_methods[] = {
  {"free", ODB__free__meth},
  {"add_backend", ODB__add_backend__meth},
  {"add_alternate", ODB__add_alternate__meth},
  {"read", ODB__read__meth},
  {"read_prefix", ODB__read_prefix__meth},
  {"read_header", ODB__read_header__meth},
  {"exists", ODB__exists__meth},
  {"write", ODB__write__meth},
  {NULL, NULL}
};

static const luaL_reg obj_ODB_metas[] = {
  {"__gc", ODB__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_ODB_bases[] = {
  {-1, NULL}
};

static const obj_field obj_ODB_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_ODB_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_ODBBackend_pub_funcs[] = {
  {"new", ODBBackend__new__meth},
  {NULL, NULL}
};

static const luaL_reg obj_ODBBackend_methods[] = {
  {NULL, NULL}
};

static const luaL_reg obj_ODBBackend_metas[] = {
  {"__gc", ODBBackend__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_ODBBackend_bases[] = {
  {-1, NULL}
};

static const obj_field obj_ODBBackend_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_ODBBackend_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Index_pub_funcs[] = {
  {"bare", Index__bare__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Index_methods[] = {
  {"clear", Index__clear__meth},
  {"read", Index__read__meth},
  {"write", Index__write__meth},
  {"find", Index__find__meth},
  {"uniq", Index__uniq__meth},
  {"add", Index__add__meth},
  {"add2", Index__add2__meth},
  {"append", Index__append__meth},
  {"append2", Index__append2__meth},
  {"remove", Index__remove__meth},
  {"get", Index__get__meth},
  {"entrycount", Index__entrycount__meth},
  {"entrycount_unmerged", Index__entrycount_unmerged__meth},
  {"get_unmerged_bypath", Index__get_unmerged_bypath__meth},
  {"get_unmerged_byindex", Index__get_unmerged_byindex__meth},
  {"read_tree", Index__read_tree__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Index_metas[] = {
  {"__gc", Index__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Index_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Index_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Index_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_IndexEntry_pub_funcs[] = {
  {"new", IndexEntry__new__meth},
  {NULL, NULL}
};

static const luaL_reg obj_IndexEntry_methods[] = {
  {"stage", IndexEntry__stage__meth},
  {"ctime", IndexEntry__ctime__meth},
  {"set_ctime", IndexEntry__set_ctime__meth},
  {"mtime", IndexEntry__mtime__meth},
  {"set_mtime", IndexEntry__set_mtime__meth},
  {"path", IndexEntry__path__meth},
  {"set_path", IndexEntry__set_path__meth},
  {"dev", IndexEntry__dev__meth},
  {"ino", IndexEntry__ino__meth},
  {"mode", IndexEntry__mode__meth},
  {"uid", IndexEntry__uid__meth},
  {"gid", IndexEntry__gid__meth},
  {"file_size", IndexEntry__file_size__meth},
  {"oid", IndexEntry__oid__meth},
  {"flags", IndexEntry__flags__meth},
  {"flags_extended", IndexEntry__flags_extended__meth},
  {NULL, NULL}
};

static const luaL_reg obj_IndexEntry_metas[] = {
  {"__gc", IndexEntry__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_IndexEntry_bases[] = {
  {-1, NULL}
};

static const obj_field obj_IndexEntry_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_IndexEntry_constants[] = {
  {"EXTENDED", NULL, 16384, CONST_NUMBER},
  {"STAGEMASK", NULL, 12288, CONST_NUMBER},
  {"VALID", NULL, 32768, CONST_NUMBER},
  {"NAMEMASK", NULL, 4095, CONST_NUMBER},
  {"STAGESHIFT", NULL, 12, CONST_NUMBER},
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_IndexEntryUnmerged_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_reg obj_IndexEntryUnmerged_methods[] = {
  {"mode", IndexEntryUnmerged__mode__meth},
  {"oid", IndexEntryUnmerged__oid__meth},
  {"path", IndexEntryUnmerged__path__meth},
  {NULL, NULL}
};

static const luaL_reg obj_IndexEntryUnmerged_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_IndexEntryUnmerged_bases[] = {
  {-1, NULL}
};

static const obj_field obj_IndexEntryUnmerged_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_IndexEntryUnmerged_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Object_pub_funcs[] = {
  {"type2string", Object__type2string__func},
  {"string2type", Object__string2type__func},
  {NULL, NULL}
};

static const luaL_reg obj_Object_methods[] = {
  {"free", Object__free__meth},
  {"id", Object__id__meth},
  {"type", Object__type__meth},
  {"owner", Object__owner__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Object_metas[] = {
  {"__gc", Object__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Object_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Object_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Object_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Blob_pub_funcs[] = {
  {"lookup", Blob__lookup__meth},
  {"fromfile", Blob__fromfile__func},
  {"frombuffer", Blob__frombuffer__func},
  {NULL, NULL}
};

static const luaL_reg obj_Blob_methods[] = {
  {"type", Object__type__meth},
  {"free", Object__free__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"rawcontent", Blob__rawcontent__meth},
  {"rawsize", Blob__rawsize__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Blob_metas[] = {
  {"__gc", Object__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Blob_bases[] = {
  {11, NULL},
  {-1, NULL}
};

static const obj_field obj_Blob_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Blob_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Signature_pub_funcs[] = {
  {"new", Signature__new__meth},
  {"now", Signature__now__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Signature_methods[] = {
  {"name", Signature__name__meth},
  {"email", Signature__email__meth},
  {"when", Signature__when__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Signature_metas[] = {
  {"__gc", Signature__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Signature_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Signature_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Signature_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Commit_pub_funcs[] = {
  {"lookup", Commit__lookup__meth},
  {"create", Commit__create__func},
  {NULL, NULL}
};

static const luaL_reg obj_Commit_methods[] = {
  {"type", Object__type__meth},
  {"free", Object__free__meth},
  {"owner", Object__owner__meth},
  {"id", Commit__id__meth},
  {"message_encoding", Commit__message_encoding__meth},
  {"message", Commit__message__meth},
  {"time", Commit__time__meth},
  {"time_offset", Commit__time_offset__meth},
  {"committer", Commit__committer__meth},
  {"author", Commit__author__meth},
  {"tree", Commit__tree__meth},
  {"parentcount", Commit__parentcount__meth},
  {"parent", Commit__parent__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Commit_metas[] = {
  {"__gc", Object__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Commit_bases[] = {
  {11, NULL},
  {-1, NULL}
};

static const obj_field obj_Commit_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Commit_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Tree_pub_funcs[] = {
  {"lookup", Tree__lookup__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tree_methods[] = {
  {"type", Object__type__meth},
  {"free", Object__free__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"entrycount", Tree__entrycount__meth},
  {"entry_byname", Tree__entry_byname__meth},
  {"entry_byindex", Tree__entry_byindex__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tree_metas[] = {
  {"__gc", Object__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Tree_bases[] = {
  {11, NULL},
  {-1, NULL}
};

static const obj_field obj_Tree_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Tree_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_TreeEntry_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_reg obj_TreeEntry_methods[] = {
  {"name", TreeEntry__name__meth},
  {"attributes", TreeEntry__attributes__meth},
  {"id", TreeEntry__id__meth},
  {"object", TreeEntry__object__meth},
  {NULL, NULL}
};

static const luaL_reg obj_TreeEntry_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_TreeEntry_bases[] = {
  {-1, NULL}
};

static const obj_field obj_TreeEntry_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_TreeEntry_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Tag_pub_funcs[] = {
  {"lookup", Tag__lookup__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tag_methods[] = {
  {"type", Object__type__meth},
  {"free", Object__free__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"target", Tag__target__meth},
  {"name", Tag__name__meth},
  {"tagger", Tag__tagger__meth},
  {"message", Tag__message__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tag_metas[] = {
  {"__gc", Object__free__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Tag_bases[] = {
  {11, NULL},
  {-1, NULL}
};

static const obj_field obj_Tag_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Tag_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_RevWalk_pub_funcs[] = {
  {"new", RevWalk__new__meth},
  {NULL, NULL}
};

static const luaL_reg obj_RevWalk_methods[] = {
  {"close", RevWalk__close__meth},
  {"reset", RevWalk__reset__meth},
  {"push", RevWalk__push__meth},
  {"hide", RevWalk__hide__meth},
  {"next", RevWalk__next__meth},
  {"sorting", RevWalk__sorting__meth},
  {"repository", RevWalk__repository__meth},
  {NULL, NULL}
};

static const luaL_reg obj_RevWalk_metas[] = {
  {"__gc", RevWalk__close__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_RevWalk_bases[] = {
  {-1, NULL}
};

static const obj_field obj_RevWalk_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_RevWalk_constants[] = {
  {"SORT_NONE", NULL, 0, CONST_NUMBER},
  {"SORT_TIME", NULL, 2, CONST_NUMBER},
  {"SORT_REVERSE", NULL, 4, CONST_NUMBER},
  {"SORT_TOPOLOGICAL", NULL, 1, CONST_NUMBER},
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Reference_pub_funcs[] = {
  {"lookup", Reference__lookup__meth},
  {"packall", Reference__packall__func},
  {"list", Reference__list__func},
  {NULL, NULL}
};

static const luaL_reg obj_Reference_methods[] = {
  {"oid", Reference__oid__meth},
  {"set_oid", Reference__set_oid__meth},
  {"target", Reference__target__meth},
  {"set_target", Reference__set_target__meth},
  {"type", Reference__type__meth},
  {"name", Reference__name__meth},
  {"resolve", Reference__resolve__meth},
  {"owner", Reference__owner__meth},
  {"rename", Reference__rename__meth},
  {"delete", Reference__delete__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Reference_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Reference_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Reference_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Reference_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg git2_function[] = {
  {"version", git2__version__func},
  {NULL, NULL}
};

static const obj_const git2_constants[] = {
#ifdef GIT_REVWALKOVER
  {"REVWALKOVER", NULL, GIT_REVWALKOVER, CONST_NUMBER},
#endif
#ifdef GIT_ERROR
  {"ERROR", NULL, GIT_ERROR, CONST_NUMBER},
#endif
  {"REF_INVALID", NULL, 0, CONST_NUMBER},
#ifdef GIT_PASSTHROUGH
  {"PASSTHROUGH", NULL, GIT_PASSTHROUGH, CONST_NUMBER},
#endif
  {"REF_SYMBOLIC", NULL, 2, CONST_NUMBER},
#ifdef GIT_EAMBIGUOUS
  {"EAMBIGUOUS", NULL, GIT_EAMBIGUOUS, CONST_NUMBER},
#endif
#ifdef GIT_OK
  {"OK", NULL, GIT_OK, CONST_NUMBER},
#endif
  {"REF_PACKED", NULL, 4, CONST_NUMBER},
  {"REF_HAS_PEEL", NULL, 8, CONST_NUMBER},
#ifdef GIT_EBUFS
  {"EBUFS", NULL, GIT_EBUFS, CONST_NUMBER},
#endif
  {"REF_LISTALL", NULL, 7, CONST_NUMBER},
#ifdef GIT_EEXISTS
  {"EEXISTS", NULL, GIT_EEXISTS, CONST_NUMBER},
#endif
  {"REF_OID", NULL, 1, CONST_NUMBER},
#ifdef GIT_ENOTFOUND
  {"ENOTFOUND", NULL, GIT_ENOTFOUND, CONST_NUMBER},
#endif
  {NULL, NULL, 0.0 , 0}
};



static const reg_sub_module reg_sub_modules[] = {
  { &(obj_type_StrArray), REG_OBJECT, obj_StrArray_pub_funcs, obj_StrArray_methods, obj_StrArray_metas, obj_StrArray_bases, obj_StrArray_fields, obj_StrArray_constants, 0},
  { &(obj_type_Repository), REG_OBJECT, obj_Repository_pub_funcs, obj_Repository_methods, obj_Repository_metas, obj_Repository_bases, obj_Repository_fields, obj_Repository_constants, 0},
  { &(obj_type_Config), REG_OBJECT, obj_Config_pub_funcs, obj_Config_methods, obj_Config_metas, obj_Config_bases, obj_Config_fields, obj_Config_constants, 0},
  { &(obj_type_OdbObject), REG_OBJECT, obj_OdbObject_pub_funcs, obj_OdbObject_methods, obj_OdbObject_metas, obj_OdbObject_bases, obj_OdbObject_fields, obj_OdbObject_constants, 0},
  { &(obj_type_OID), REG_OBJECT, obj_OID_pub_funcs, obj_OID_methods, obj_OID_metas, obj_OID_bases, obj_OID_fields, obj_OID_constants, 0},
  { &(obj_type_OID_Shorten), REG_OBJECT, obj_OID_Shorten_pub_funcs, obj_OID_Shorten_methods, obj_OID_Shorten_metas, obj_OID_Shorten_bases, obj_OID_Shorten_fields, obj_OID_Shorten_constants, 0},
  { &(obj_type_ODB), REG_OBJECT, obj_ODB_pub_funcs, obj_ODB_methods, obj_ODB_metas, obj_ODB_bases, obj_ODB_fields, obj_ODB_constants, 0},
  { &(obj_type_ODBBackend), REG_OBJECT, obj_ODBBackend_pub_funcs, obj_ODBBackend_methods, obj_ODBBackend_metas, obj_ODBBackend_bases, obj_ODBBackend_fields, obj_ODBBackend_constants, 0},
  { &(obj_type_Index), REG_OBJECT, obj_Index_pub_funcs, obj_Index_methods, obj_Index_metas, obj_Index_bases, obj_Index_fields, obj_Index_constants, 0},
  { &(obj_type_IndexEntry), REG_OBJECT, obj_IndexEntry_pub_funcs, obj_IndexEntry_methods, obj_IndexEntry_metas, obj_IndexEntry_bases, obj_IndexEntry_fields, obj_IndexEntry_constants, 0},
  { &(obj_type_IndexEntryUnmerged), REG_OBJECT, obj_IndexEntryUnmerged_pub_funcs, obj_IndexEntryUnmerged_methods, obj_IndexEntryUnmerged_metas, obj_IndexEntryUnmerged_bases, obj_IndexEntryUnmerged_fields, obj_IndexEntryUnmerged_constants, 0},
  { &(obj_type_Object), REG_OBJECT, obj_Object_pub_funcs, obj_Object_methods, obj_Object_metas, obj_Object_bases, obj_Object_fields, obj_Object_constants, 0},
  { &(obj_type_Blob), REG_OBJECT, obj_Blob_pub_funcs, obj_Blob_methods, obj_Blob_metas, obj_Blob_bases, obj_Blob_fields, obj_Blob_constants, 0},
  { &(obj_type_Signature), REG_OBJECT, obj_Signature_pub_funcs, obj_Signature_methods, obj_Signature_metas, obj_Signature_bases, obj_Signature_fields, obj_Signature_constants, 0},
  { &(obj_type_Commit), REG_OBJECT, obj_Commit_pub_funcs, obj_Commit_methods, obj_Commit_metas, obj_Commit_bases, obj_Commit_fields, obj_Commit_constants, 0},
  { &(obj_type_Tree), REG_OBJECT, obj_Tree_pub_funcs, obj_Tree_methods, obj_Tree_metas, obj_Tree_bases, obj_Tree_fields, obj_Tree_constants, 0},
  { &(obj_type_TreeEntry), REG_OBJECT, obj_TreeEntry_pub_funcs, obj_TreeEntry_methods, obj_TreeEntry_metas, obj_TreeEntry_bases, obj_TreeEntry_fields, obj_TreeEntry_constants, 0},
  { &(obj_type_Tag), REG_OBJECT, obj_Tag_pub_funcs, obj_Tag_methods, obj_Tag_metas, obj_Tag_bases, obj_Tag_fields, obj_Tag_constants, 0},
  { &(obj_type_RevWalk), REG_OBJECT, obj_RevWalk_pub_funcs, obj_RevWalk_methods, obj_RevWalk_metas, obj_RevWalk_bases, obj_RevWalk_fields, obj_RevWalk_constants, 0},
  { &(obj_type_Reference), REG_OBJECT, obj_Reference_pub_funcs, obj_Reference_methods, obj_Reference_metas, obj_Reference_bases, obj_Reference_fields, obj_Reference_constants, 0},
  {NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0}
};





#if LUAJIT_FFI
static const ffi_export_symbol git2_ffi_export[] = {
  {NULL, { NULL } }
};
#endif




static const luaL_Reg submodule_libs[] = {
  {NULL, NULL}
};



static void create_object_instance_cache(lua_State *L) {
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(!lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop weak table. */
		return;
	}
	lua_pop(L, 1); /* pop nil. */
	/* create weak table for object instance references. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_newtable(L);               /* weak table. */
	lua_newtable(L);               /* metatable for weak table. */
	lua_pushliteral(L, "__mode");
	lua_pushliteral(L, "v");
	lua_rawset(L, -3);             /* metatable.__mode = 'v'  weak values. */
	lua_setmetatable(L, -2);       /* add metatable to weak table. */
	lua_rawset(L, LUA_REGISTRYINDEX);  /* create reference to weak table. */
}

LUA_NOBJ_API int luaopen_git2(lua_State *L) {
	const reg_sub_module *reg = reg_sub_modules;
	const luaL_Reg *submodules = submodule_libs;
	int priv_table = -1;

	/* private table to hold reference to object metatables. */
	lua_newtable(L);
	priv_table = lua_gettop(L);
	lua_pushlightuserdata(L, obj_udata_private_key);
	lua_pushvalue(L, priv_table);
	lua_rawset(L, LUA_REGISTRYINDEX);  /* store private table in registry. */

	/* create object cache. */
	create_object_instance_cache(L);

	/* module table. */
#if REG_MODULES_AS_GLOBALS
	luaL_register(L, "git2", git2_function);
#else
	lua_newtable(L);
	luaL_register(L, NULL, git2_function);
#endif

	/* register module constants. */
	obj_type_register_constants(L, git2_constants, -1, 0);

	for(; submodules->func != NULL ; submodules++) {
		lua_pushcfunction(L, submodules->func);
		lua_pushstring(L, submodules->name);
		lua_call(L, 1, 0);
	}

	/* register objects */
	for(; reg->type != NULL ; reg++) {
		lua_newtable(L); /* create public API table for object. */
		lua_pushvalue(L, -1); /* dup. object's public API table. */
		lua_setfield(L, -3, reg->type->name); /* module["<object_name>"] = <object public API> */
#if REG_OBJECTS_AS_GLOBALS
		lua_pushvalue(L, -1);                 /* dup value. */
		lua_setglobal(L, reg->type->name);    /* global: <object_name> = <object public API> */
#endif
		obj_type_register(L, reg, priv_table);
	}

#if LUAJIT_FFI
	if(nobj_check_ffi_support(L)) {
		nobj_try_loading_ffi(L, "git2", git2_ffi_lua_code,
			git2_ffi_export, priv_table);
	}
#endif



	return 1;
}


