luagit2
=======

LibGit2 bindings for Lua.

Installing
----------

### Install lua-git2:

curl -O "https://github.com/Neopallium/luagit2/raw/master/lua-git2-scm-0.rockspec"

luarocks install lua-git2-scm-0.rockspec


Build Dependencies
------------------

Optional dependency for re-generating Lua bindings from *.nobj.lua files:

* [LuaNativeObjects](https://github.com/Neopallium/LuaNativeObjects), this is the bindings generator used to convert the *.nobj.lua files into a native Lua module.

