
c_module "git2" {
-- module settings.
use_globals = false,
hide_meta_info = false, --true,

include "git2.h",

subfiles {
"repository.nobj.lua",
"database.nobj.lua",
"rawobject.nobj.lua",
"index.nobj.lua",
"index_entry.nobj.lua",
"oid.nobj.lua",
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

