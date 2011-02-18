
c_module "git2" {
-- module settings.
use_globals = false,
hide_meta_info = false, --true,

include "git2.h",

-- Error codes
const "SUCCESS"        { 0 },
const "ERROR"          { -1 },
const "ENOTOID"        { -2 },
const "ENOTFOUND"      { -3 },
const "ENOMEM"         { -4 },
const "EOSERR"         { -5 },
const "EOBJTYPE"       { -6 },
const "EOBJCORRUPTED"  { -7 },
const "ENOTAREPO"      { -8 },
const "EINVALIDTYPE"   { -9 },
const "EMISSINGOBJDATA"{ -10 },
const "EPACKCORRUPTED" { -11 },
const "EFLOCKFAIL"     { -12 },
const "EZLIB"          { -13 },
const "EBUSY"          { -14 },
const "EBAREINDEX"     { -15 },

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

