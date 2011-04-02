
c_module "git2" {
-- module settings.
use_globals = false,
hide_meta_info = false, --true,

include "git2.h",

-- Error codes
export_definitions {
SUCCESS               = "GIT_SUCCESS",
ERROR                 = "GIT_ERROR",
ENOTOID               = "GIT_ENOTOID",
ENOTFOUND             = "GIT_ENOTFOUND",
ENOMEM                = "GIT_ENOMEM",
EOSERR                = "GIT_EOSERR",
EOBJTYPE              = "GIT_EOBJTYPE",
EOBJCORRUPTED         = "GIT_EOBJCORRUPTED",
ENOTAREPO             = "GIT_ENOTAREPO",
EINVALIDTYPE          = "GIT_EINVALIDTYPE",
EMISSINGOBJDATA       = "GIT_EMISSINGOBJDATA",
EPACKCORRUPTED        = "GIT_EPACKCORRUPTED",
EFLOCKFAIL            = "GIT_EFLOCKFAIL",
EZLIB                 = "GIT_EZLIB",
EBUSY                 = "GIT_EBUSY",
EBAREINDEX            = "GIT_EBAREINDEX",
EINVALIDREFNAME       = "GIT_EINVALIDREFNAME",
EREFCORRUPTED         = "GIT_EREFCORRUPTED",
ETOONESTEDSYMREF      = "GIT_ETOONESTEDSYMREF",
EPACKEDREFSCORRUPTED  = "GIT_EPACKEDREFSCORRUPTED",
EINVALIDPATH          = "GIT_EINVALIDPATH",
EREVWALKOVER          = "GIT_EREVWALKOVER",
EINVALIDREFSTATE      = "GIT_EINVALIDREFSTATE",
ENOTIMPLEMENTED       = "GIT_ENOTIMPLEMENTED",
EEXISTS               = "GIT_EEXISTS",
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

subfiles {
"src/strarray.nobj.lua",
"src/error.nobj.lua",
"src/repository.nobj.lua",
"src/odb_object.nobj.lua",
"src/oid.nobj.lua",
"src/database.nobj.lua",
--"src/database_backend.nobj.lua",
"src/index.nobj.lua",
"src/index_entry.nobj.lua",
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

