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

#include "git2.h"


#define REG_PACKAGE_IS_CONSTRUCTOR 0
#define REG_OBJECTS_AS_GLOBALS 0
#define OBJ_DATA_HIDDEN_METATABLE 0
#define LUAJIT_FFI 0
#define USE_FIELD_GET_SET_METHODS 0



#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER

/* define some types that we need. */
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

#define FUNC_UNUSED

#else

#include <stdint.h>

#define FUNC_UNUSED __attribute__((unused))

#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define assert_obj_type(type, obj) \
	assert(__builtin_types_compatible_p(typeof(obj), type *))
#else
#define assert_obj_type(type, obj)
#endif

#ifndef obj_type_free
#define obj_type_free(type, obj) do { \
	assert_obj_type(type, obj); \
	free((obj)); \
} while(0)
#endif

#ifndef obj_type_new
#define obj_type_new(type, obj) do { \
	assert_obj_type(type, obj); \
	(obj) = malloc(sizeof(type)); \
} while(0)
#endif

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

typedef struct reg_sub_module {
	obj_type        *type;
	int             is_package;
	const luaL_reg  *pub_funcs;
	const luaL_reg  *methods;
	const luaL_reg  *metas;
	const obj_base  *bases;
	const obj_field *fields;
	const obj_const *constants;
} reg_sub_module;

#define OBJ_UDATA_FLAG_OWN (1<<0)
#define OBJ_UDATA_FLAG_LOOKUP (1<<1)
#define OBJ_UDATA_LAST_FLAG (OBJ_UDATA_FLAG_LOOKUP)
typedef struct obj_udata {
	void     *obj;
	uint32_t flags;  /**< lua_own:1bit */
} obj_udata;

/* use static pointer as key to weak userdata table. */
static char *obj_udata_weak_ref_key = "obj_udata_weak_ref_key";

#if LUAJIT_FFI
typedef struct ffi_export_symbol {
	const char *name;
	void       *sym;
} ffi_export_symbol;
#endif


#define obj_type_id_Repository 0
#define obj_type_Repository_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Repository))
#define obj_type_Repository_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Repository), flags)
#define obj_type_Repository_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Repository), flags)

#define obj_type_id_RawObject 1
#define obj_type_RawObject_check(L, _index) \
  (RawObject *)obj_simple_udata_luacheck(L, _index, &(obj_type_RawObject))
#define obj_type_RawObject_delete(L, _index, flags) \
  (RawObject *)obj_simple_udata_luadelete(L, _index, &(obj_type_RawObject), flags)
#define obj_type_RawObject_push(L, obj, flags) \
  obj_simple_udata_luapush(L, obj, sizeof(RawObject), &(obj_type_RawObject))

#define obj_type_id_OID 2
#define obj_type_OID_check(L, _index) \
  *((OID *)obj_simple_udata_luacheck(L, _index, &(obj_type_OID)))
#define obj_type_OID_delete(L, _index, flags) \
  *((OID *)obj_simple_udata_luadelete(L, _index, &(obj_type_OID), flags))
#define obj_type_OID_push(L, obj, flags) \
  obj_simple_udata_luapush(L, &(obj), sizeof(OID), &(obj_type_OID))

#define obj_type_id_Database 3
#define obj_type_Database_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Database))
#define obj_type_Database_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Database), flags)
#define obj_type_Database_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Database), flags)

#define obj_type_id_DatabaseBackend 4
#define obj_type_DatabaseBackend_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_DatabaseBackend))
#define obj_type_DatabaseBackend_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_DatabaseBackend), flags)
#define obj_type_DatabaseBackend_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_DatabaseBackend), flags)

#define obj_type_id_Index 5
#define obj_type_Index_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Index))
#define obj_type_Index_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Index), flags)
#define obj_type_Index_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Index), flags)

#define obj_type_id_IndexEntry 6
#define obj_type_IndexEntry_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_IndexEntry))
#define obj_type_IndexEntry_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_IndexEntry), flags)
#define obj_type_IndexEntry_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_IndexEntry), flags)

#define obj_type_id_Object 7
#define obj_type_Object_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Object))
#define obj_type_Object_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Object), flags)
#define obj_type_Object_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Object), flags)

#define obj_type_id_Blob 8
#define obj_type_Blob_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Blob))
#define obj_type_Blob_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Blob), flags)
#define obj_type_Blob_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Blob), flags)

#define obj_type_id_Signature 9
#define obj_type_Signature_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Signature))
#define obj_type_Signature_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Signature), flags)
#define obj_type_Signature_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Signature), flags)

#define obj_type_id_Commit 10
#define obj_type_Commit_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Commit))
#define obj_type_Commit_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Commit), flags)
#define obj_type_Commit_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Commit), flags)

#define obj_type_id_Tree 11
#define obj_type_Tree_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Tree))
#define obj_type_Tree_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Tree), flags)
#define obj_type_Tree_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Tree), flags)

#define obj_type_id_TreeEntry 12
#define obj_type_TreeEntry_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_TreeEntry))
#define obj_type_TreeEntry_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_TreeEntry), flags)
#define obj_type_TreeEntry_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_TreeEntry), flags)

#define obj_type_id_Tag 13
#define obj_type_Tag_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_Tag))
#define obj_type_Tag_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_Tag), flags)
#define obj_type_Tag_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Tag), flags)

#define obj_type_id_RevWalk 14
#define obj_type_RevWalk_check(L, _index) \
  obj_udata_luacheck(L, _index, &(obj_type_RevWalk))
#define obj_type_RevWalk_delete(L, _index, flags) \
  obj_udata_luadelete(L, _index, &(obj_type_RevWalk), flags)
#define obj_type_RevWalk_push(L, obj, flags) \
  obj_udata_luapush_weak(L, (void *)obj, &(obj_type_RevWalk), flags)



typedef int GitError;

static void error_code__GitError__push(lua_State *L, GitError err);
static void dyn_caster_Object(void **obj, obj_type **type);


static obj_type obj_type_Repository = { NULL, 0, OBJ_TYPE_FLAG_WEAK_REF, "Repository" };
static obj_type obj_type_RawObject = { NULL, 1, OBJ_TYPE_SIMPLE, "RawObject" };
static obj_type obj_type_OID = { NULL, 2, OBJ_TYPE_SIMPLE, "OID" };
static obj_type obj_type_Database = { NULL, 3, OBJ_TYPE_FLAG_WEAK_REF, "Database" };
static obj_type obj_type_DatabaseBackend = { NULL, 4, OBJ_TYPE_FLAG_WEAK_REF, "DatabaseBackend" };
static obj_type obj_type_Index = { NULL, 5, OBJ_TYPE_FLAG_WEAK_REF, "Index" };
static obj_type obj_type_IndexEntry = { NULL, 6, OBJ_TYPE_FLAG_WEAK_REF, "IndexEntry" };
static obj_type obj_type_Object = { dyn_caster_Object, 7, OBJ_TYPE_FLAG_WEAK_REF, "Object" };
static obj_type obj_type_Blob = { NULL, 8, OBJ_TYPE_FLAG_WEAK_REF, "Blob" };
static obj_type obj_type_Signature = { NULL, 9, OBJ_TYPE_FLAG_WEAK_REF, "Signature" };
static obj_type obj_type_Commit = { NULL, 10, OBJ_TYPE_FLAG_WEAK_REF, "Commit" };
static obj_type obj_type_Tree = { NULL, 11, OBJ_TYPE_FLAG_WEAK_REF, "Tree" };
static obj_type obj_type_TreeEntry = { NULL, 12, OBJ_TYPE_FLAG_WEAK_REF, "TreeEntry" };
static obj_type obj_type_Tag = { NULL, 13, OBJ_TYPE_FLAG_WEAK_REF, "Tag" };
static obj_type obj_type_RevWalk = { NULL, 14, OBJ_TYPE_FLAG_WEAK_REF, "RevWalk" };


#ifndef REG_PACKAGE_IS_CONSTRUCTOR
#define REG_PACKAGE_IS_CONSTRUCTOR 1
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

static FUNC_UNUSED obj_udata *obj_udata_luacheck_internal(lua_State *L, int _index, void **obj, obj_type *type) {
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
					luaL_error(L, "null %s", type->name); /* object was garbage collected? */
				}
				return ud;
			}
		}
	}
	luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	return NULL;
}

static FUNC_UNUSED void *obj_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	obj_udata_luacheck_internal(L, _index, &(obj), type);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type);
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable to invalidate userdata. */
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
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	lua_setmetatable(L, -2);
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

	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));

	/* init. obj_udata. */
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
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
	}
	luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	return NULL;
}

static FUNC_UNUSED void * obj_simple_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj = obj_simple_udata_luacheck(L, _index, type);
	*flags = OBJ_UDATA_FLAG_OWN;
	/* clear the metatable to invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void obj_simple_udata_luapush(lua_State *L, void *obj, int size, obj_type *type)
{
	/* create new userdata. */
	void *ud = lua_newuserdata(L, size);
	memcpy(ud, obj, size);
	/* get obj_type metatable. */
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	lua_setmetatable(L, -2);
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

static void obj_type_register_constants(lua_State *L, const obj_const *constants, int tab_idx) {
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
		lua_rawset(L, tab_idx - 2);
		constants++;
	}
}

static void obj_type_register_package(lua_State *L, const reg_sub_module *type_reg) {
	obj_type *type = type_reg->type;
	const luaL_reg *reg_list = type_reg->pub_funcs;

	/* create public functions table. */
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1);

	lua_pop(L, 1);  /* drop package table */
}

static void obj_type_register(lua_State *L, const reg_sub_module *type_reg, int priv_table) {
	const luaL_reg *reg_list;
	obj_type *type = type_reg->type;
	const obj_base *base = type_reg->bases;

	if(type_reg->is_package == 1) {
		return obj_type_register_package(L, type_reg);
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
		lua_setmetatable(L, -2);

		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
	} else {
		/* register all methods as public functions. */
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

#if LUAJIT_FFI
	/* add metatable to 'priv_table' */
	lua_pushstring(L, type->name);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, priv_table);    /* priv_table["<object_name>"] = metatable */
#endif

	luaL_register(L, NULL, type_reg->metas); /* fill metatable */

	/* add obj_bases to metatable. */
	while(base->id >= 0) {
		lua_pushlightuserdata(L, (void *)base);
		lua_rawseti(L, -2, base->id);
		base++;
	}

	obj_type_register_constants(L, type_reg->constants, -2);

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table */
	lua_rawset(L, -3);                  /* metatable.__index = methods */
#if OBJ_DATA_HIDDEN_METATABLE
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, -3);               /* dup methods table */
	lua_rawset(L, -3);                  /* hide metatable:
	                                       metatable.__metatable = methods */
#endif
	lua_pop(L, 2);                      /* drop metatable & methods */
}

static FUNC_UNUSED int lua_checktype_ref(lua_State *L, int _index, int _type) {
	luaL_checktype(L,_index,_type);
	lua_pushvalue(L,_index);
	return luaL_ref(L, LUA_REGISTRYINDEX);
}

#if LUAJIT_FFI
static int nobj_udata_new_ffi(lua_State *L) {
	size_t size = luaL_checkinteger(L, 1);
	void *ud;
	luaL_checktype(L, 2, LUA_TTABLE);
	lua_settop(L, 2);
	/* create userdata. */
	ud = lua_newuserdata(L, size);
	lua_replace(L, 1);
	/* set userdata's metatable. */
	lua_setmetatable(L, 1);
	return 1;
}

static int nobj_try_loading_ffi(lua_State *L, const char *ffi_mod_name,
		const char *ffi_init_code, const ffi_export_symbol *ffi_exports, int priv_table)
{
	int err;

	/* export symbols to priv_table. */
	while(ffi_exports->name != NULL) {
		lua_pushstring(L, ffi_exports->name);
		lua_pushlightuserdata(L, ffi_exports->sym);
		lua_settable(L, priv_table);
		ffi_exports++;
	}
	err = luaL_loadbuffer(L, ffi_init_code, strlen(ffi_init_code), ffi_mod_name);
	if(0 == err) {
		lua_pushvalue(L, -2); /* dup C module's table. */
		lua_pushvalue(L, priv_table); /* move priv_table to top of stack. */
		lua_remove(L, priv_table);
		lua_pushcfunction(L, nobj_udata_new_ffi);
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




typedef git_repository Repository;

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

static void RawObject_from_git_rawobj(lua_State *L, RawObject *raw, git_rawobj *git, int cleanup) {
	/* push raw object's data onto stack. */
	lua_pushlstring(L, git->data, git->len);
	/* get Lua's pointer to the string. */
	raw->git.data = (void *)lua_tolstring(L, -1, &(raw->git.len));
	raw->git.type = git->type;
	/* get reference to string. */
	raw->ref = luaL_ref(L, LUA_REGISTRYINDEX);
	/* clean-up git_rawobj. */
	if(cleanup && git->data != NULL) {
		git_rawobj_close(git);
	}
}

static void RawObject_close(lua_State *L, RawObject *raw) {
	luaL_unref(L, LUA_REGISTRYINDEX, raw->ref);
	raw->ref = LUA_REFNIL;
	raw->git.data = NULL;
}


typedef git_oid OID;

typedef git_odb Database;

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
		/* copy header fields. */
		obj->len = raw_obj->git.len;
		obj->type = raw_obj->git.type;
		/* we must malloc & copy the RawObject's data. */
		if(raw_obj->git.data) {
			obj->data = malloc(obj->len);
			if(obj->data == NULL) {
				/* failed to allocate buffer. */
				return GIT_ENOMEM;
			}
			/* copy data. */
			memcpy(obj->data, raw_obj->git.data, obj->len);
		} else {
			obj->data = NULL;
		}
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
		/* copy only header fields. */
		obj->data = NULL;
		obj->len = raw_obj->git.len;
		obj->type = raw_obj->git.type;
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
	RawObject_from_git_rawobj(L, &raw, obj, 0);
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


typedef git_index Index;

typedef git_index_entry IndexEntry;

typedef git_object Object;

typedef git_blob Blob;

typedef git_signature Signature;

typedef git_commit Commit;

typedef git_tree Tree;

typedef git_tree_entry TreeEntry;

typedef git_tag Tag;

typedef git_revwalk RevWalk;



/* method: open */
static int Repository__open__meth(lua_State *L) {
  size_t path_len_idx1;
  const char * path_idx1 = luaL_checklstring(L,1,&(path_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Repository * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_repository_open(&(this_idx1), path_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Repository_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: open2 */
static int Repository__open2__meth(lua_State *L) {
  size_t dir_len_idx1;
  const char * dir_idx1 = luaL_checklstring(L,1,&(dir_len_idx1));
  size_t object_directory_len_idx2;
  const char * object_directory_idx2 = luaL_checklstring(L,2,&(object_directory_len_idx2));
  size_t index_file_len_idx3;
  const char * index_file_idx3 = luaL_checklstring(L,3,&(index_file_len_idx3));
  size_t work_tree_len_idx4;
  const char * work_tree_idx4 = luaL_checklstring(L,4,&(work_tree_len_idx4));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Repository * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_repository_open2(&(this_idx1), dir_idx1, object_directory_idx2, index_file_idx3, work_tree_idx4);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Repository_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: open3 */
static int Repository__open3__meth(lua_State *L) {
  size_t dir_len_idx1;
  const char * dir_idx1 = luaL_checklstring(L,1,&(dir_len_idx1));
  Database * object_database_idx2 = obj_type_Database_check(L,2);
  size_t index_file_len_idx3;
  const char * index_file_idx3 = luaL_checklstring(L,3,&(index_file_len_idx3));
  size_t work_tree_len_idx4;
  const char * work_tree_idx4 = luaL_checklstring(L,4,&(work_tree_len_idx4));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Repository * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_repository_open3(&(this_idx1), dir_idx1, object_database_idx2, index_file_idx3, work_tree_idx4);
  if(!(GIT_SUCCESS != err_idx2)) {
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
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_repository_init(&(this_idx1), path_idx1, is_bare_idx2);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Repository_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: delete */
static int Repository__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Repository * this_idx1 = obj_type_Repository_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_repository_free(this_idx1);
  return 0;
}

/* method: database */
static int Repository__database__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  Database * rc_git_repository_database_idx1;
  rc_git_repository_database_idx1 = git_repository_database(this_idx1);
  obj_type_Database_push(L, rc_git_repository_database_idx1, 0);
  return 1;
}

/* method: index */
static int Repository__index__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  Index * index_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_repository_index(&(index_idx1), this_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Index_push(L, index_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: lookup */
static int Repository__lookup__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  size_t type_len_idx3;
  const char * type_idx3 = luaL_checklstring(L,3,&(type_len_idx3));
  Object * obj_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  int otype_idx3 = 0;
  otype_idx3 = git_object_string2type(type_idx3);
  err_idx2 = git_repository_lookup(&(obj_idx1), this_idx1, &(id_idx2), otype_idx3);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Object_push(L, obj_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: newobject */
static int Repository__newobject__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  size_t type_len_idx2;
  const char * type_idx2 = luaL_checklstring(L,2,&(type_len_idx2));
  Object * obj_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  int otype_idx3 = 0;
  otype_idx3 = git_object_string2type(type_idx2);
  err_idx2 = git_repository_newobject(&(obj_idx1), this_idx1, otype_idx3);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Object_push(L, obj_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: blob_writefile */
static int Repository__blob_writefile__meth(lua_State *L) {
  Repository * this_idx1 = obj_type_Repository_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  OID written_id_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_blob_writefile(&(written_id_idx1), this_idx1, path_idx2);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_OID_push(L, written_id_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: new */
static int RawObject__new__meth(lua_State *L) {
  size_t type_len_idx1;
  const char * type_idx1 = luaL_checklstring(L,1,&(type_len_idx1));
  size_t data_len_idx2;
  const char * data_idx2 = luaL_checklstring(L,2,&(data_len_idx2));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  RawObject * this_idx1 = NULL;
	RawObject raw; /* temp. storage, this gets copied. */
	this_idx1 = &(raw);
	raw.git.type = git_object_string2type(type_idx1);
	raw.ref = LUA_REFNIL;
	RawObject_set_data_and_ref(L, &raw, data_idx2, data_len_idx2, 2);

  obj_type_RawObject_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: header */
static int RawObject__header__meth(lua_State *L) {
  size_t type_len_idx1;
  const char * type_idx1 = luaL_checklstring(L,1,&(type_len_idx1));
  size_t len_idx2 = luaL_checkinteger(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  RawObject * this_idx1 = NULL;
	RawObject raw; /* temp. storage, this gets copied. */
	this_idx1 = &(raw);
	raw.git.data = NULL;
	raw.git.len = len_idx2;
	raw.git.type = git_object_string2type(type_idx1);
	raw.ref = LUA_REFNIL;

  obj_type_RawObject_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: delete */
static int RawObject__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  RawObject * this_idx1 = obj_type_RawObject_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
	RawObject_close(L, this_idx1);

  return 0;
}

/* method: close */
static int RawObject__close__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
	RawObject_close(L, this_idx1);

  return 0;
}

/* method: data */
static int RawObject__data__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
	/* push Lua string. */
	lua_rawgeti(L, LUA_REGISTRYINDEX, this_idx1->ref);

  return 1;
}

/* method: set_data */
static int RawObject__set_data__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
  size_t data_len_idx2;
  const char * data_idx2 = luaL_checklstring(L,2,&(data_len_idx2));
	RawObject_set_data_and_ref(L, this_idx1, data_idx2, data_len_idx2, 2);

  return 0;
}

/* method: len */
static int RawObject__len__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
  size_t len_idx1 = 0;
	len_idx1 = this_idx1->git.len;

  lua_pushinteger(L, len_idx1);
  return 1;
}

/* method: type */
static int RawObject__type__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
  const char * type_idx1 = NULL;
type_idx1 = git_object_type2string(this_idx1->git.type);
  lua_pushstring(L, type_idx1);
  return 1;
}

/* method: set_type */
static int RawObject__set_type__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
  size_t type_len_idx2;
  const char * type_idx2 = luaL_checklstring(L,2,&(type_len_idx2));
this_idx1->git.type = git_object_string2type(type_idx2);
  return 0;
}

/* method: hash */
static int RawObject__hash__meth(lua_State *L) {
  RawObject * this_idx1 = obj_type_RawObject_check(L,1);
  OID id_idx1;
  GitError err_idx2 = GIT_SUCCESS;
	err_idx2 = git_rawobj_hash(&(id_idx1), &(this_idx1->git));

  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_OID_push(L, id_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: str */
static int OID__str__meth(lua_State *L) {
  size_t hex_len_idx1;
  const char * hex_idx1 = luaL_checklstring(L,1,&(hex_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  OID this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_oid_mkstr(&(this_idx1), hex_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_OID_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: raw */
static int OID__raw__meth(lua_State *L) {
  size_t raw_len_idx1;
  const unsigned char * raw_idx1 = luaL_checklstring(L,1,&(raw_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  OID this_idx1;
  git_oid_mkraw(&(this_idx1), raw_idx1);
  obj_type_OID_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: __str__ */
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

/* method: __eq__ */
static int OID____eq____meth(lua_State *L) {
  OID this_idx1 = obj_type_OID_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int ret_idx1 = 0;
  ret_idx1 = git_oid_cmp(&(this_idx1), &(id_idx2));
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: new */
static int Database__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Database * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_odb_new(&(this_idx1));
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Database_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: open */
static int Database__open__meth(lua_State *L) {
  size_t object_dir_len_idx1;
  const char * object_dir_idx1 = luaL_checklstring(L,1,&(object_dir_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Database * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_odb_open(&(this_idx1), object_dir_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Database_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: close */
static int Database__close__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Database * this_idx1 = obj_type_Database_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_odb_close(this_idx1);
  return 0;
}

/* method: add_backend */
static int Database__add_backend__meth(lua_State *L) {
  Database * this_idx1 = obj_type_Database_check(L,1);
  DatabaseBackend * backend_idx2 = obj_type_DatabaseBackend_check(L,2);
  int priority_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_SUCCESS;
	err_idx1 = git_odb_add_backend(this_idx1, &(backend_idx2->backend), priority_idx3);
	DatabaseBackend_ref(backend_idx2);

  /* check for error. */
  if((GIT_SUCCESS != err_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: add_alternate */
static int Database__add_alternate__meth(lua_State *L) {
  Database * this_idx1 = obj_type_Database_check(L,1);
  DatabaseBackend * backend_idx2 = obj_type_DatabaseBackend_check(L,2);
  int priority_idx3 = luaL_checkinteger(L,3);
  GitError err_idx1 = GIT_SUCCESS;
	err_idx1 = git_odb_add_alternate(this_idx1, &(backend_idx2->backend), priority_idx3);
	DatabaseBackend_ref(backend_idx2);

  /* check for error. */
  if((GIT_SUCCESS != err_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: read */
static int Database__read__meth(lua_State *L) {
  Database * this_idx1 = obj_type_Database_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  RawObject * obj_idx1 = NULL;
  GitError err_idx2 = GIT_SUCCESS;
	RawObject raw;
	git_rawobj git;
	err_idx2 = git_odb_read(&(git), this_idx1, &(id_idx2));
	if(err_idx2 == GIT_SUCCESS) {
		/* convert git_rawobj to RawObject */
		RawObject_from_git_rawobj(L, &raw, &git, 1);
		obj_idx1 = &(raw);
	}

  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_RawObject_push(L, obj_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: read_header */
static int Database__read_header__meth(lua_State *L) {
  Database * this_idx1 = obj_type_Database_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  RawObject * obj_idx1 = NULL;
  GitError err_idx2 = GIT_SUCCESS;
	RawObject raw;
	git_rawobj git;
	err_idx2 = git_odb_read_header(&(git), this_idx1, &(id_idx2));
	if(err_idx2 == GIT_SUCCESS) {
		/* convert git_rawobj to RawObject */
		RawObject_from_git_rawobj(L, &raw, &git, 1);
		obj_idx1 = &(raw);
	}

  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_RawObject_push(L, obj_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: write */
static int Database__write__meth(lua_State *L) {
  Database * this_idx1 = obj_type_Database_check(L,1);
  RawObject * obj_idx2 = obj_type_RawObject_check(L,2);
  OID id_idx1;
  GitError err_idx2 = GIT_SUCCESS;
	err_idx2 = git_odb_write(&(id_idx1), this_idx1, &(obj_idx2->git));

  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_OID_push(L, id_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: exists */
static int Database__exists__meth(lua_State *L) {
  Database * this_idx1 = obj_type_Database_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  GitError err_idx1 = GIT_SUCCESS;
  err_idx1 = git_odb_exists(this_idx1, &(id_idx2));
  /* check for error. */
  if((GIT_SUCCESS != err_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: new */
static int DatabaseBackend__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  DatabaseBackend * this_idx1;
	int idx;
	int ref;

	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 1);
	/* create backend object. */
	this_idx1 = calloc(1, sizeof(DatabaseBackend));
	this_idx1->ref_count = 1;
	this_idx1->L = L;
	/* get each callback from table. */
#define REF_CB(_name) \
	lua_getfield(L, 1, "on_" #_name); \
	this_idx1->_name = luaL_ref(L, LUA_REGISTRYINDEX); \
	this_idx1->backend._name = database_backend_ ## _name ## _cb;

	REF_CB(read)
	REF_CB(read_header)
	REF_CB(write)
	REF_CB(exists)
	REF_CB(free)
#undef REF_CB

  obj_type_DatabaseBackend_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: delete */
static int DatabaseBackend__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  DatabaseBackend * this_idx1 = obj_type_DatabaseBackend_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
	DatabaseBackend_unref(this_idx1);

  return 0;
}

/* method: bare */
static int Index__bare__meth(lua_State *L) {
  size_t index_path_len_idx1;
  const char * index_path_idx1 = luaL_checklstring(L,1,&(index_path_len_idx1));
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Index * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_index_open_bare(&(this_idx1), index_path_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Index_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: inrepo */
static int Index__inrepo__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Index * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_index_open_inrepo(&(this_idx1), repo_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Index_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: delete */
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
  GitError rc_git_index_read_idx1 = GIT_SUCCESS;
  rc_git_index_read_idx1 = git_index_read(this_idx1);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_index_read_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_index_read_idx1);
  } else {
    lua_pushboolean(L, 1);
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

/* method: add */
static int Index__add__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  int stage_idx3 = luaL_checkinteger(L,3);
  GitError rc_git_index_add_idx1 = GIT_SUCCESS;
  rc_git_index_add_idx1 = git_index_add(this_idx1, path_idx2, stage_idx3);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_index_add_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_index_add_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: remove */
static int Index__remove__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  int position_idx2 = luaL_checkinteger(L,2);
  GitError rc_git_index_remove_idx1 = GIT_SUCCESS;
  rc_git_index_remove_idx1 = git_index_remove(this_idx1, position_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_index_remove_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_index_remove_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: insert */
static int Index__insert__meth(lua_State *L) {
  Index * this_idx1 = obj_type_Index_check(L,1);
  IndexEntry * source_entry_idx2 = obj_type_IndexEntry_check(L,2);
  GitError rc_git_index_insert_idx1 = GIT_SUCCESS;
  rc_git_index_insert_idx1 = git_index_insert(this_idx1, source_entry_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_index_insert_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_index_insert_idx1);
  } else {
    lua_pushboolean(L, 1);
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

/* method: new */
static int IndexEntry__new__meth(lua_State *L) {
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  IndexEntry * this_idx1;
	this_idx1 = calloc(1, sizeof(IndexEntry));

  obj_type_IndexEntry_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: delete */
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

/* method: ctime */
static int IndexEntry__ctime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  time_t secs_idx1 = 0;
  time_t nanosecs_idx2 = 0;
	secs_idx1 = this_idx1->ctime.seconds;
	nanosecs_idx2 = this_idx1->ctime.nanoseconds;

  lua_pushinteger(L, secs_idx1);
  lua_pushinteger(L, nanosecs_idx2);
  return 2;
}

/* method: set_ctime */
static int IndexEntry__set_ctime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  time_t secs_idx2 = luaL_checkinteger(L,2);
  time_t nanosecs_idx3 = luaL_checkinteger(L,3);
	this_idx1->ctime.seconds = secs_idx2;
	this_idx1->ctime.nanoseconds = nanosecs_idx3;

  return 0;
}

/* method: mtime */
static int IndexEntry__mtime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  time_t secs_idx1 = 0;
  time_t nanosecs_idx2 = 0;
	secs_idx1 = this_idx1->mtime.seconds;
	nanosecs_idx2 = this_idx1->mtime.nanoseconds;

  lua_pushinteger(L, secs_idx1);
  lua_pushinteger(L, nanosecs_idx2);
  return 2;
}

/* method: set_mtime */
static int IndexEntry__set_mtime__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  time_t secs_idx2 = luaL_checkinteger(L,2);
  time_t nanosecs_idx3 = luaL_checkinteger(L,3);
	this_idx1->mtime.seconds = secs_idx2;
	this_idx1->mtime.nanoseconds = nanosecs_idx3;

  return 0;
}

/* method: dev */
static int IndexEntry__dev__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int ret_idx1 = 0;
ret_idx1 = this_idx1->dev;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_dev */
static int IndexEntry__set_dev__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int val_idx2 = luaL_checkinteger(L,2);
this_idx1->dev = val_idx2;
  return 0;
}

/* method: ino */
static int IndexEntry__ino__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int ret_idx1 = 0;
ret_idx1 = this_idx1->ino;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_ino */
static int IndexEntry__set_ino__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int val_idx2 = luaL_checkinteger(L,2);
this_idx1->ino = val_idx2;
  return 0;
}

/* method: mode */
static int IndexEntry__mode__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int ret_idx1 = 0;
ret_idx1 = this_idx1->mode;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_mode */
static int IndexEntry__set_mode__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int val_idx2 = luaL_checkinteger(L,2);
this_idx1->mode = val_idx2;
  return 0;
}

/* method: uid */
static int IndexEntry__uid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int ret_idx1 = 0;
ret_idx1 = this_idx1->uid;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_uid */
static int IndexEntry__set_uid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int val_idx2 = luaL_checkinteger(L,2);
this_idx1->uid = val_idx2;
  return 0;
}

/* method: gid */
static int IndexEntry__gid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int ret_idx1 = 0;
ret_idx1 = this_idx1->gid;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_gid */
static int IndexEntry__set_gid__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned int val_idx2 = luaL_checkinteger(L,2);
this_idx1->gid = val_idx2;
  return 0;
}

/* method: file_size */
static int IndexEntry__file_size__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  off_t ret_idx1 = 0;
ret_idx1 = this_idx1->file_size;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_file_size */
static int IndexEntry__set_file_size__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  off_t val_idx2 = luaL_checkinteger(L,2);
this_idx1->file_size = val_idx2;
  return 0;
}

/* method: id */
static int IndexEntry__id__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  OID ret_idx1;
ret_idx1 = this_idx1->oid;
  obj_type_OID_push(L, ret_idx1, 0);
  return 1;
}

/* method: set_id */
static int IndexEntry__set_id__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  OID val_idx2 = obj_type_OID_check(L,2);
this_idx1->oid = val_idx2;
  return 0;
}

/* method: flags */
static int IndexEntry__flags__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned short ret_idx1 = 0;
ret_idx1 = this_idx1->flags;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_flags */
static int IndexEntry__set_flags__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned short val_idx2 = luaL_checkinteger(L,2);
this_idx1->flags = val_idx2;
  return 0;
}

/* method: flags_extended */
static int IndexEntry__flags_extended__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned short ret_idx1 = 0;
ret_idx1 = this_idx1->flags_extended;
  lua_pushinteger(L, ret_idx1);
  return 1;
}

/* method: set_flags_extended */
static int IndexEntry__set_flags_extended__meth(lua_State *L) {
  IndexEntry * this_idx1 = obj_type_IndexEntry_check(L,1);
  unsigned short val_idx2 = luaL_checkinteger(L,2);
this_idx1->flags_extended = val_idx2;
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

static void error_code__GitError__push(lua_State *L, GitError err) {
  const char *err_str = NULL;
	if(err != GIT_SUCCESS) {
		err_str = git_strerror(err);
	}

	if(err_str) {
		lua_pushstring(L, err_str);
	} else {
		lua_pushnil(L);
	}
}

/* method: delete */
static int Object__delete__meth(lua_State *L) {
  int this_flags_idx1 = 0;
  Object * this_idx1 = obj_type_Object_delete(L,1,&(this_flags_idx1));
  if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN)) { return 0; }
  git_object_free(this_idx1);
  return 0;
}

/* method: write */
static int Object__write__meth(lua_State *L) {
  Object * this_idx1 = obj_type_Object_check(L,1);
  GitError rc_git_object_write_idx1 = GIT_SUCCESS;
  rc_git_object_write_idx1 = git_object_write(this_idx1);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_object_write_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_object_write_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: id */
static int Object__id__meth(lua_State *L) {
  Object * this_idx1 = obj_type_Object_check(L,1);
  OID id_idx1;
	id_idx1 = *(git_object_id(this_idx1));

  obj_type_OID_push(L, id_idx1, 0);
  return 1;
}

/* method: type */
static int Object__type__meth(lua_State *L) {
  Object * this_idx1 = obj_type_Object_check(L,1);
  const char * type_idx1 = NULL;
type_idx1 = git_object_type2string(git_object_type(this_idx1));
  lua_pushstring(L, type_idx1);
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

static void dyn_caster_Object(void **obj, obj_type **type) {
  Object * base_obj = (Object *)*obj;
  switch(git_object_type(base_obj)) {
  case GIT_OBJ_BLOB:
    *type = &(obj_type_Blob);
    break;
  case GIT_OBJ_TREE:
    *type = &(obj_type_Tree);
    break;
  case GIT_OBJ_COMMIT:
    *type = &(obj_type_Commit);
    break;
  default:
    break;
  }
}

/* method: new */
static int Blob__new__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Blob * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_blob_new(&(this_idx1), repo_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Blob_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: lookup */
static int Blob__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Blob * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_blob_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Blob_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: writefile */
static int Blob__writefile__func(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  size_t path_len_idx2;
  const char * path_idx2 = luaL_checklstring(L,2,&(path_len_idx2));
  OID written_id_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_blob_writefile(&(written_id_idx1), repo_idx1, path_idx2);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_OID_push(L, written_id_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: set_rawcontent_fromfile */
static int Blob__set_rawcontent_fromfile__meth(lua_State *L) {
  Blob * this_idx1 = obj_type_Blob_check(L,1);
  size_t filename_len_idx2;
  const char * filename_idx2 = luaL_checklstring(L,2,&(filename_len_idx2));
  GitError err_idx1 = GIT_SUCCESS;
  err_idx1 = git_blob_set_rawcontent_fromfile(this_idx1, filename_idx2);
  /* check for error. */
  if((GIT_SUCCESS != err_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: set_rawcontent */
static int Blob__set_rawcontent__meth(lua_State *L) {
  Blob * this_idx1 = obj_type_Blob_check(L,1);
  size_t buffer_len_idx2;
  const char * buffer_idx2 = luaL_checklstring(L,2,&(buffer_len_idx2));
  GitError err_idx1 = GIT_SUCCESS;
  err_idx1 = git_blob_set_rawcontent(this_idx1, buffer_idx2, buffer_len_idx2);
  /* check for error. */
  if((GIT_SUCCESS != err_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, err_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: rawcontent */
static int Blob__rawcontent__meth(lua_State *L) {
  Blob * this_idx1 = obj_type_Blob_check(L,1);
  size_t buffer_len_idx1 = 0;
  const char * buffer_idx1 = NULL;
	buffer_idx1 = git_blob_rawcontent(this_idx1);
	buffer_len_idx1 = git_blob_rawsize(this_idx1);

  if(buffer_idx1 == NULL) lua_pushnil(L);  else lua_pushlstring(L, buffer_idx1,buffer_len_idx1);
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
  time_t time_idx3 = luaL_checkinteger(L,3);
  int offset_idx4 = luaL_checkinteger(L,4);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Signature * this_idx1;
  this_idx1 = git_signature_new(name_idx1, email_idx2, time_idx3, offset_idx4);
  obj_type_Signature_push(L, this_idx1, this_flags_idx1);
  return 1;
}

/* method: delete */
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
  time_t time_idx1 = 0;
  int offset_idx2 = 0;
time_idx1 = this_idx1->when.time; offset_idx2 = this_idx1->when.offset;
  lua_pushinteger(L, time_idx1);
  lua_pushinteger(L, offset_idx2);
  return 2;
}

/* method: new */
static int Commit__new__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Commit * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_commit_new(&(this_idx1), repo_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Commit_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: lookup */
static int Commit__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Commit * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_commit_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Commit_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: message */
static int Commit__message__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const char * rc_git_commit_message_idx1 = NULL;
  rc_git_commit_message_idx1 = git_commit_message(this_idx1);
  lua_pushstring(L, rc_git_commit_message_idx1);
  return 1;
}

/* method: message_short */
static int Commit__message_short__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const char * rc_git_commit_message_short_idx1 = NULL;
  rc_git_commit_message_short_idx1 = git_commit_message_short(this_idx1);
  lua_pushstring(L, rc_git_commit_message_short_idx1);
  return 1;
}

/* method: set_message */
static int Commit__set_message__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  size_t message_len_idx2;
  const char * message_idx2 = luaL_checklstring(L,2,&(message_len_idx2));
  git_commit_set_message(this_idx1, message_idx2);
  return 0;
}

/* method: time */
static int Commit__time__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  time_t rc_git_commit_time_idx1 = 0;
  rc_git_commit_time_idx1 = git_commit_time(this_idx1);
  lua_pushinteger(L, rc_git_commit_time_idx1);
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

/* method: set_committer */
static int Commit__set_committer__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const Signature * sig_idx2 = obj_type_Signature_check(L,2);
  git_commit_set_committer(this_idx1, sig_idx2);
  return 0;
}

/* method: author */
static int Commit__author__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const Signature * rc_git_commit_author_idx1;
  rc_git_commit_author_idx1 = git_commit_author(this_idx1);
  obj_type_Signature_push(L, rc_git_commit_author_idx1, 0);
  return 1;
}

/* method: set_author */
static int Commit__set_author__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const Signature * sig_idx2 = obj_type_Signature_check(L,2);
  git_commit_set_author(this_idx1, sig_idx2);
  return 0;
}

/* method: tree */
static int Commit__tree__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  const Tree * rc_git_commit_tree_idx1;
  rc_git_commit_tree_idx1 = git_commit_tree(this_idx1);
  obj_type_Tree_push(L, rc_git_commit_tree_idx1, 0);
  return 1;
}

/* method: set_tree */
static int Commit__set_tree__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  Tree * tree_idx2 = obj_type_Tree_check(L,2);
  git_commit_set_tree(this_idx1, tree_idx2);
  return 0;
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
  Commit * rc_git_commit_parent_idx1;
  rc_git_commit_parent_idx1 = git_commit_parent(this_idx1, n_idx2);
  obj_type_Commit_push(L, rc_git_commit_parent_idx1, 0);
  return 1;
}

/* method: add_parent */
static int Commit__add_parent__meth(lua_State *L) {
  Commit * this_idx1 = obj_type_Commit_check(L,1);
  Commit * parent_idx2 = obj_type_Commit_check(L,2);
  GitError rc_git_commit_add_parent_idx1 = GIT_SUCCESS;
  rc_git_commit_add_parent_idx1 = git_commit_add_parent(this_idx1, parent_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_commit_add_parent_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_commit_add_parent_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: new */
static int Tree__new__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tree * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_tree_new(&(this_idx1), repo_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Tree_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: lookup */
static int Tree__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tree * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_tree_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_SUCCESS != err_idx2)) {
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
  TreeEntry * rc_git_tree_entry_byname_idx1;
  rc_git_tree_entry_byname_idx1 = git_tree_entry_byname(this_idx1, filename_idx2);
  obj_type_TreeEntry_push(L, rc_git_tree_entry_byname_idx1, 0);
  return 1;
}

/* method: entry_byindex */
static int Tree__entry_byindex__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  int index_idx2 = luaL_checkinteger(L,2);
  TreeEntry * rc_git_tree_entry_byindex_idx1;
  rc_git_tree_entry_byindex_idx1 = git_tree_entry_byindex(this_idx1, index_idx2);
  obj_type_TreeEntry_push(L, rc_git_tree_entry_byindex_idx1, 0);
  return 1;
}

/* method: add_entry */
static int Tree__add_entry__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  const OID id_idx2 = obj_type_OID_check(L,2);
  size_t filename_len_idx3;
  const char * filename_idx3 = luaL_checklstring(L,3,&(filename_len_idx3));
  int attributes_idx4 = luaL_checkinteger(L,4);
  TreeEntry * entry_out_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_tree_add_entry(&(entry_out_idx1), this_idx1, &(id_idx2), filename_idx3, attributes_idx4);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_TreeEntry_push(L, entry_out_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: remove_entry_byname */
static int Tree__remove_entry_byname__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  size_t filename_len_idx2;
  const char * filename_idx2 = luaL_checklstring(L,2,&(filename_len_idx2));
  GitError rc_git_tree_remove_entry_byname_idx1 = GIT_SUCCESS;
  rc_git_tree_remove_entry_byname_idx1 = git_tree_remove_entry_byname(this_idx1, filename_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_tree_remove_entry_byname_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_tree_remove_entry_byname_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: remove_entry_byindex */
static int Tree__remove_entry_byindex__meth(lua_State *L) {
  Tree * this_idx1 = obj_type_Tree_check(L,1);
  int index_idx2 = luaL_checkinteger(L,2);
  GitError rc_git_tree_remove_entry_byindex_idx1 = GIT_SUCCESS;
  rc_git_tree_remove_entry_byindex_idx1 = git_tree_remove_entry_byindex(this_idx1, index_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_tree_remove_entry_byindex_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_tree_remove_entry_byindex_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: name */
static int TreeEntry__name__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  const char * rc_git_tree_entry_name_idx1 = NULL;
  rc_git_tree_entry_name_idx1 = git_tree_entry_name(this_idx1);
  lua_pushstring(L, rc_git_tree_entry_name_idx1);
  return 1;
}

/* method: set_name */
static int TreeEntry__set_name__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  git_tree_entry_set_name(this_idx1, name_idx2);
  return 0;
}

/* method: attributes */
static int TreeEntry__attributes__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  unsigned int rc_git_tree_entry_attributes_idx1 = 0;
  rc_git_tree_entry_attributes_idx1 = git_tree_entry_attributes(this_idx1);
  lua_pushinteger(L, rc_git_tree_entry_attributes_idx1);
  return 1;
}

/* method: set_attributes */
static int TreeEntry__set_attributes__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  int attr_idx2 = luaL_checkinteger(L,2);
  git_tree_entry_set_attributes(this_idx1, attr_idx2);
  return 0;
}

/* method: id */
static int TreeEntry__id__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  OID id_idx1;
id_idx1 = *(git_tree_entry_id(this_idx1));
  obj_type_OID_push(L, id_idx1, 0);
  return 1;
}

/* method: set_id */
static int TreeEntry__set_id__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  git_tree_entry_set_id(this_idx1, &(id_idx2));
  return 0;
}

/* method: object */
static int TreeEntry__object__meth(lua_State *L) {
  TreeEntry * this_idx1 = obj_type_TreeEntry_check(L,1);
  Object * obj_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_tree_entry_2object(&(obj_idx1), this_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Object_push(L, obj_idx1, 0);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: new */
static int Tag__new__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tag * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_tag_new(&(this_idx1), repo_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_Tag_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: lookup */
static int Tag__lookup__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  OID id_idx2 = obj_type_OID_check(L,2);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  Tag * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_tag_lookup(&(this_idx1), repo_idx1, &(id_idx2));
  if(!(GIT_SUCCESS != err_idx2)) {
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
  const Object * rc_git_tag_target_idx1;
  rc_git_tag_target_idx1 = git_tag_target(this_idx1);
  obj_type_Object_push(L, rc_git_tag_target_idx1, 0);
  return 1;
}

/* method: set_target */
static int Tag__set_target__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  Object * target_idx2 = obj_type_Object_check(L,2);
  git_tag_set_target(this_idx1, target_idx2);
  return 0;
}

/* method: name */
static int Tag__name__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const char * rc_git_tag_name_idx1 = NULL;
  rc_git_tag_name_idx1 = git_tag_name(this_idx1);
  lua_pushstring(L, rc_git_tag_name_idx1);
  return 1;
}

/* method: set_name */
static int Tag__set_name__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  size_t name_len_idx2;
  const char * name_idx2 = luaL_checklstring(L,2,&(name_len_idx2));
  git_tag_set_name(this_idx1, name_idx2);
  return 0;
}

/* method: tagger */
static int Tag__tagger__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const Signature * rc_git_tag_tagger_idx1;
  rc_git_tag_tagger_idx1 = git_tag_tagger(this_idx1);
  obj_type_Signature_push(L, rc_git_tag_tagger_idx1, 0);
  return 1;
}

/* method: set_tagger */
static int Tag__set_tagger__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const Signature * tagger_idx2 = obj_type_Signature_check(L,2);
  git_tag_set_tagger(this_idx1, tagger_idx2);
  return 0;
}

/* method: message */
static int Tag__message__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  const char * rc_git_tag_message_idx1 = NULL;
  rc_git_tag_message_idx1 = git_tag_message(this_idx1);
  lua_pushstring(L, rc_git_tag_message_idx1);
  return 1;
}

/* method: set_message */
static int Tag__set_message__meth(lua_State *L) {
  Tag * this_idx1 = obj_type_Tag_check(L,1);
  size_t message_len_idx2;
  const char * message_idx2 = luaL_checklstring(L,2,&(message_len_idx2));
  git_tag_set_message(this_idx1, message_idx2);
  return 0;
}

/* method: new */
static int RevWalk__new__meth(lua_State *L) {
  Repository * repo_idx1 = obj_type_Repository_check(L,1);
  int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
  RevWalk * this_idx1;
  GitError err_idx2 = GIT_SUCCESS;
  err_idx2 = git_revwalk_new(&(this_idx1), repo_idx1);
  if(!(GIT_SUCCESS != err_idx2)) {
    obj_type_RevWalk_push(L, this_idx1, this_flags_idx1);
  } else {
    lua_pushnil(L);
  }
  error_code__GitError__push(L, err_idx2);
  return 2;
}

/* method: delete */
static int RevWalk__delete__meth(lua_State *L) {
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
  Commit * commit_idx2 = obj_type_Commit_check(L,2);
  GitError rc_git_revwalk_push_idx1 = GIT_SUCCESS;
  rc_git_revwalk_push_idx1 = git_revwalk_push(this_idx1, commit_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_revwalk_push_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_revwalk_push_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: hide */
static int RevWalk__hide__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  Commit * commit_idx2 = obj_type_Commit_check(L,2);
  GitError rc_git_revwalk_hide_idx1 = GIT_SUCCESS;
  rc_git_revwalk_hide_idx1 = git_revwalk_hide(this_idx1, commit_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_revwalk_hide_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_revwalk_hide_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: next */
static int RevWalk__next__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  Commit * commit_idx1;
  GitError rc_git_revwalk_next_idx2 = GIT_SUCCESS;
  rc_git_revwalk_next_idx2 = git_revwalk_next(&(commit_idx1), this_idx1);
  if(!(GIT_SUCCESS != rc_git_revwalk_next_idx2)) {
    obj_type_Commit_push(L, commit_idx1, 0);
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
  GitError rc_git_revwalk_sorting_idx1 = GIT_SUCCESS;
  rc_git_revwalk_sorting_idx1 = git_revwalk_sorting(this_idx1, sort_mode_idx2);
  /* check for error. */
  if((GIT_SUCCESS != rc_git_revwalk_sorting_idx1)) {
    lua_pushboolean(L, 0);
      error_code__GitError__push(L, rc_git_revwalk_sorting_idx1);
  } else {
    lua_pushboolean(L, 1);
  }
  return 2;
}

/* method: repository */
static int RevWalk__repository__meth(lua_State *L) {
  RevWalk * this_idx1 = obj_type_RevWalk_check(L,1);
  Repository * rc_git_revwalk_repository_idx1;
  rc_git_revwalk_repository_idx1 = git_revwalk_repository(this_idx1);
  obj_type_Repository_push(L, rc_git_revwalk_repository_idx1, 0);
  return 1;
}



static const luaL_reg obj_Repository_pub_funcs[] = {
  {"open", Repository__open__meth},
  {"open2", Repository__open2__meth},
  {"open3", Repository__open3__meth},
  {"init", Repository__init__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Repository_methods[] = {
  {"database", Repository__database__meth},
  {"index", Repository__index__meth},
  {"lookup", Repository__lookup__meth},
  {"newobject", Repository__newobject__meth},
  {"blob_writefile", Repository__blob_writefile__meth},
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

static const luaL_reg obj_RawObject_pub_funcs[] = {
  {"new", RawObject__new__meth},
  {"header", RawObject__header__meth},
  {NULL, NULL}
};

static const luaL_reg obj_RawObject_methods[] = {
  {"close", RawObject__close__meth},
  {"data", RawObject__data__meth},
  {"set_data", RawObject__set_data__meth},
  {"len", RawObject__len__meth},
  {"type", RawObject__type__meth},
  {"set_type", RawObject__set_type__meth},
  {"hash", RawObject__hash__meth},
  {NULL, NULL}
};

static const luaL_reg obj_RawObject_metas[] = {
  {"__gc", RawObject__delete__meth},
  {"__tostring", obj_simple_udata_default_tostring},
  {"__eq", obj_simple_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_RawObject_bases[] = {
  {-1, NULL}
};

static const obj_field obj_RawObject_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_RawObject_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_OID_pub_funcs[] = {
  {"str", OID__str__meth},
  {"raw", OID__raw__meth},
  {NULL, NULL}
};

static const luaL_reg obj_OID_methods[] = {
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
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Database_pub_funcs[] = {
  {"new", Database__new__meth},
  {"open", Database__open__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Database_methods[] = {
  {"close", Database__close__meth},
  {"add_backend", Database__add_backend__meth},
  {"add_alternate", Database__add_alternate__meth},
  {"read", Database__read__meth},
  {"read_header", Database__read_header__meth},
  {"write", Database__write__meth},
  {"exists", Database__exists__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Database_metas[] = {
  {"__gc", Database__close__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Database_bases[] = {
  {-1, NULL}
};

static const obj_field obj_Database_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Database_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_DatabaseBackend_pub_funcs[] = {
  {"new", DatabaseBackend__new__meth},
  {NULL, NULL}
};

static const luaL_reg obj_DatabaseBackend_methods[] = {
  {NULL, NULL}
};

static const luaL_reg obj_DatabaseBackend_metas[] = {
  {"__gc", DatabaseBackend__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_DatabaseBackend_bases[] = {
  {-1, NULL}
};

static const obj_field obj_DatabaseBackend_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_DatabaseBackend_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Index_pub_funcs[] = {
  {"bare", Index__bare__meth},
  {"inrepo", Index__inrepo__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Index_methods[] = {
  {"clear", Index__clear__meth},
  {"read", Index__read__meth},
  {"find", Index__find__meth},
  {"add", Index__add__meth},
  {"remove", Index__remove__meth},
  {"insert", Index__insert__meth},
  {"get", Index__get__meth},
  {"entrycount", Index__entrycount__meth},
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
  {"ctime", IndexEntry__ctime__meth},
  {"set_ctime", IndexEntry__set_ctime__meth},
  {"mtime", IndexEntry__mtime__meth},
  {"set_mtime", IndexEntry__set_mtime__meth},
  {"dev", IndexEntry__dev__meth},
  {"set_dev", IndexEntry__set_dev__meth},
  {"ino", IndexEntry__ino__meth},
  {"set_ino", IndexEntry__set_ino__meth},
  {"mode", IndexEntry__mode__meth},
  {"set_mode", IndexEntry__set_mode__meth},
  {"uid", IndexEntry__uid__meth},
  {"set_uid", IndexEntry__set_uid__meth},
  {"gid", IndexEntry__gid__meth},
  {"set_gid", IndexEntry__set_gid__meth},
  {"file_size", IndexEntry__file_size__meth},
  {"set_file_size", IndexEntry__set_file_size__meth},
  {"id", IndexEntry__id__meth},
  {"set_id", IndexEntry__set_id__meth},
  {"flags", IndexEntry__flags__meth},
  {"set_flags", IndexEntry__set_flags__meth},
  {"flags_extended", IndexEntry__flags_extended__meth},
  {"set_flags_extended", IndexEntry__set_flags_extended__meth},
  {"path", IndexEntry__path__meth},
  {"set_path", IndexEntry__set_path__meth},
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

static const luaL_reg obj_Object_pub_funcs[] = {
  {NULL, NULL}
};

static const luaL_reg obj_Object_methods[] = {
  {"write", Object__write__meth},
  {"id", Object__id__meth},
  {"type", Object__type__meth},
  {"owner", Object__owner__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Object_metas[] = {
  {"__gc", Object__delete__meth},
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
  {"new", Blob__new__meth},
  {"lookup", Blob__lookup__meth},
  {"writefile", Blob__writefile__func},
  {NULL, NULL}
};

static const luaL_reg obj_Blob_methods[] = {
  {"type", Object__type__meth},
  {"write", Object__write__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"delete", Object__delete__meth},
  {"set_rawcontent_fromfile", Blob__set_rawcontent_fromfile__meth},
  {"set_rawcontent", Blob__set_rawcontent__meth},
  {"rawcontent", Blob__rawcontent__meth},
  {"rawsize", Blob__rawsize__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Blob_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Blob_bases[] = {
  {7, NULL},
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
  {"new", Commit__new__meth},
  {"lookup", Commit__lookup__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Commit_methods[] = {
  {"type", Object__type__meth},
  {"write", Object__write__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"delete", Object__delete__meth},
  {"message", Commit__message__meth},
  {"message_short", Commit__message_short__meth},
  {"set_message", Commit__set_message__meth},
  {"time", Commit__time__meth},
  {"committer", Commit__committer__meth},
  {"set_committer", Commit__set_committer__meth},
  {"author", Commit__author__meth},
  {"set_author", Commit__set_author__meth},
  {"tree", Commit__tree__meth},
  {"set_tree", Commit__set_tree__meth},
  {"parentcount", Commit__parentcount__meth},
  {"parent", Commit__parent__meth},
  {"add_parent", Commit__add_parent__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Commit_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Commit_bases[] = {
  {7, NULL},
  {-1, NULL}
};

static const obj_field obj_Commit_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_Commit_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const luaL_reg obj_Tree_pub_funcs[] = {
  {"new", Tree__new__meth},
  {"lookup", Tree__lookup__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tree_methods[] = {
  {"type", Object__type__meth},
  {"write", Object__write__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"delete", Object__delete__meth},
  {"entrycount", Tree__entrycount__meth},
  {"entry_byname", Tree__entry_byname__meth},
  {"entry_byindex", Tree__entry_byindex__meth},
  {"add_entry", Tree__add_entry__meth},
  {"remove_entry_byname", Tree__remove_entry_byname__meth},
  {"remove_entry_byindex", Tree__remove_entry_byindex__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tree_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Tree_bases[] = {
  {7, NULL},
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
  {"set_name", TreeEntry__set_name__meth},
  {"attributes", TreeEntry__attributes__meth},
  {"set_attributes", TreeEntry__set_attributes__meth},
  {"id", TreeEntry__id__meth},
  {"set_id", TreeEntry__set_id__meth},
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
  {"new", Tag__new__meth},
  {"lookup", Tag__lookup__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tag_methods[] = {
  {"type", Object__type__meth},
  {"write", Object__write__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"delete", Object__delete__meth},
  {"target", Tag__target__meth},
  {"set_target", Tag__set_target__meth},
  {"name", Tag__name__meth},
  {"set_name", Tag__set_name__meth},
  {"tagger", Tag__tagger__meth},
  {"set_tagger", Tag__set_tagger__meth},
  {"message", Tag__message__meth},
  {"set_message", Tag__set_message__meth},
  {NULL, NULL}
};

static const luaL_reg obj_Tag_metas[] = {
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_Tag_bases[] = {
  {7, NULL},
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
  {"type", Object__type__meth},
  {"write", Object__write__meth},
  {"id", Object__id__meth},
  {"owner", Object__owner__meth},
  {"reset", RevWalk__reset__meth},
  {"push", RevWalk__push__meth},
  {"hide", RevWalk__hide__meth},
  {"next", RevWalk__next__meth},
  {"sorting", RevWalk__sorting__meth},
  {"repository", RevWalk__repository__meth},
  {NULL, NULL}
};

static const luaL_reg obj_RevWalk_metas[] = {
  {"__gc", RevWalk__delete__meth},
  {"__tostring", obj_udata_default_tostring},
  {"__eq", obj_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_RevWalk_bases[] = {
  {7, NULL},
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

static const luaL_reg git2_function[] = {
  {NULL, NULL}
};

static const obj_const git2_constants[] = {
  {"EFLOCKFAIL", NULL, -12, CONST_NUMBER},
  {"SUCCESS", NULL, 0, CONST_NUMBER},
  {"EBUSY", NULL, -14, CONST_NUMBER},
  {"EMISSINGOBJDATA", NULL, -10, CONST_NUMBER},
  {"EBAREINDEX", NULL, -15, CONST_NUMBER},
  {"EOSERR", NULL, -5, CONST_NUMBER},
  {"ERROR", NULL, -1, CONST_NUMBER},
  {"EZLIB", NULL, -13, CONST_NUMBER},
  {"ENOTFOUND", NULL, -3, CONST_NUMBER},
  {"EOBJTYPE", NULL, -6, CONST_NUMBER},
  {"ENOTOID", NULL, -2, CONST_NUMBER},
  {"EPACKCORRUPTED", NULL, -11, CONST_NUMBER},
  {"EINVALIDTYPE", NULL, -9, CONST_NUMBER},
  {"ENOTAREPO", NULL, -8, CONST_NUMBER},
  {"ENOMEM", NULL, -4, CONST_NUMBER},
  {"EOBJCORRUPTED", NULL, -7, CONST_NUMBER},
  {NULL, NULL, 0.0 , 0}
};



static const reg_sub_module reg_sub_modules[] = {
  { &(obj_type_Repository), 0, obj_Repository_pub_funcs, obj_Repository_methods, obj_Repository_metas, obj_Repository_bases, obj_Repository_fields, obj_Repository_constants},
  { &(obj_type_RawObject), 0, obj_RawObject_pub_funcs, obj_RawObject_methods, obj_RawObject_metas, obj_RawObject_bases, obj_RawObject_fields, obj_RawObject_constants},
  { &(obj_type_OID), 0, obj_OID_pub_funcs, obj_OID_methods, obj_OID_metas, obj_OID_bases, obj_OID_fields, obj_OID_constants},
  { &(obj_type_Database), 0, obj_Database_pub_funcs, obj_Database_methods, obj_Database_metas, obj_Database_bases, obj_Database_fields, obj_Database_constants},
  { &(obj_type_DatabaseBackend), 0, obj_DatabaseBackend_pub_funcs, obj_DatabaseBackend_methods, obj_DatabaseBackend_metas, obj_DatabaseBackend_bases, obj_DatabaseBackend_fields, obj_DatabaseBackend_constants},
  { &(obj_type_Index), 0, obj_Index_pub_funcs, obj_Index_methods, obj_Index_metas, obj_Index_bases, obj_Index_fields, obj_Index_constants},
  { &(obj_type_IndexEntry), 0, obj_IndexEntry_pub_funcs, obj_IndexEntry_methods, obj_IndexEntry_metas, obj_IndexEntry_bases, obj_IndexEntry_fields, obj_IndexEntry_constants},
  { &(obj_type_Object), 0, obj_Object_pub_funcs, obj_Object_methods, obj_Object_metas, obj_Object_bases, obj_Object_fields, obj_Object_constants},
  { &(obj_type_Blob), 0, obj_Blob_pub_funcs, obj_Blob_methods, obj_Blob_metas, obj_Blob_bases, obj_Blob_fields, obj_Blob_constants},
  { &(obj_type_Signature), 0, obj_Signature_pub_funcs, obj_Signature_methods, obj_Signature_metas, obj_Signature_bases, obj_Signature_fields, obj_Signature_constants},
  { &(obj_type_Commit), 0, obj_Commit_pub_funcs, obj_Commit_methods, obj_Commit_metas, obj_Commit_bases, obj_Commit_fields, obj_Commit_constants},
  { &(obj_type_Tree), 0, obj_Tree_pub_funcs, obj_Tree_methods, obj_Tree_metas, obj_Tree_bases, obj_Tree_fields, obj_Tree_constants},
  { &(obj_type_TreeEntry), 0, obj_TreeEntry_pub_funcs, obj_TreeEntry_methods, obj_TreeEntry_metas, obj_TreeEntry_bases, obj_TreeEntry_fields, obj_TreeEntry_constants},
  { &(obj_type_Tag), 0, obj_Tag_pub_funcs, obj_Tag_methods, obj_Tag_metas, obj_Tag_bases, obj_Tag_fields, obj_Tag_constants},
  { &(obj_type_RevWalk), 0, obj_RevWalk_pub_funcs, obj_RevWalk_methods, obj_RevWalk_metas, obj_RevWalk_bases, obj_RevWalk_fields, obj_RevWalk_constants},
  {NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL}
};







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

int luaopen_git2(lua_State *L) {
	const reg_sub_module *reg = reg_sub_modules;
	const luaL_Reg *submodules = submodule_libs;
	int priv_table = -1;

#if LUAJIT_FFI
	/* private table to hold reference to object metatables. */
	lua_newtable(L);
	priv_table = lua_gettop(L);
#endif

	/* create object cache. */
	create_object_instance_cache(L);

	/* module table. */
	luaL_register(L, "git2", git2_function);

	/* register module constants. */
	obj_type_register_constants(L, git2_constants, -1);

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
	nobj_try_loading_ffi(L, "git2", git2_ffi_lua_code,
		git2_ffi_export, priv_table);
#endif
	return 1;
}


