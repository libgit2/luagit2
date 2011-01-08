
c_module "git2" {
-- module settings.
use_globals = false,
hide_meta_info = false, --true,

include "git2.h",

package "GIT" {
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
},

subfiles {
"repository.nobj.lua",
"rawobject.nobj.lua",
"oid.nobj.lua",
"database.nobj.lua",
"database_backend.nobj.lua",
"index.nobj.lua",
"index_entry.nobj.lua",
"error.nobj.lua",
"object.nobj.lua",
"blob.nobj.lua",
"signature.nobj.lua",
"commit.nobj.lua",
"tree.nobj.lua",
"tree_entry.nobj.lua",
"tag.nobj.lua",
"revwalk.nobj.lua",
},
}

