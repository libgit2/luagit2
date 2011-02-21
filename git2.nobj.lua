
c_module "git2" {
-- module settings.
use_globals = false,
hide_meta_info = false, --true,

include "git2.h",

-- Error codes
constants {
SUCCESS         = 0,
ERROR           = -1,
ENOTOID         = -2,
ENOTFOUND       = -3,
ENOMEM          = -4,
EOSERR          = -5,
EOBJTYPE        = -6,
EOBJCORRUPTED   = -7,
ENOTAREPO       = -8,
EINVALIDTYPE    = -9,
EMISSINGOBJDATA = -10,
EPACKCORRUPTED  = -11,
EFLOCKFAIL      = -12,
EZLIB           = -13,
EBUSY           = -14,
EBAREINDEX      = -15,
},

subfiles {
"src/repository.nobj.lua",
"src/rawobject.nobj.lua",
"src/oid.nobj.lua",
"src/database.nobj.lua",
"src/database_backend.nobj.lua",
"src/index.nobj.lua",
"src/index_entry.nobj.lua",
"src/error.nobj.lua",
"src/object.nobj.lua",
"src/blob.nobj.lua",
"src/signature.nobj.lua",
"src/commit.nobj.lua",
"src/tree.nobj.lua",
"src/tree_entry.nobj.lua",
"src/tag.nobj.lua",
"src/revwalk.nobj.lua",
},
}

