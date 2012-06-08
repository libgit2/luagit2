
basetype "git_time_t"  "integer" "0"

c_module "git2" {
-- module settings.
use_globals = false,
hide_meta_info = false, --true,

include "git2.h",

-- Error codes
export_definitions {
OK                    = "GIT_OK",
ERROR                 = "GIT_ERROR",
ENOTFOUND             = "GIT_ENOTFOUND",
EEXISTS               = "GIT_EEXISTS",
EAMBIGUOUS            = "GIT_EAMBIGUOUS",
EBUFS                 = "GIT_EBUFS",

PASSTHROUGH           = "GIT_PASSTHROUGH",
REVWALKOVER           = "GIT_REVWALKOVER",
},

-- reference types
constants {
REF_INVALID  = 0,    -- Invalid reference */
REF_OID      = 1,    -- A reference which points at an object id */
REF_SYMBOLIC = 2,    -- A reference which points at another reference */
REF_PACKED   = 4,
REF_HAS_PEEL = 8,
REF_LISTALL  = 0x07, -- GIT_REF_OID|GIT_REF_SYMBOLIC|GIT_REF_PACKED,
},

c_function "version" {
	var_out{ "<any>", "ver" },
	c_source[[
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
]],
},
subfiles {
"src/strarray.nobj.lua",
"src/error.nobj.lua",
"src/repository.nobj.lua",
"src/config.nobj.lua",
"src/odb_object.nobj.lua",
"src/oid.nobj.lua",
"src/oid_shorten.nobj.lua",
"src/odb.nobj.lua",
"src/odb_backend.nobj.lua",
"src/index.nobj.lua",
"src/index_entry.nobj.lua",
"src/index_entry_unmerged.nobj.lua",
"src/object.nobj.lua",
"src/blob.nobj.lua",
"src/signature.nobj.lua",
"src/commit.nobj.lua",
"src/tree.nobj.lua",
"src/tree_entry.nobj.lua",
"src/tag.nobj.lua",
"src/revwalk.nobj.lua",
"src/reference.nobj.lua",
},
}

