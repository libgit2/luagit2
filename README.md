luagit2
=======

LibGit2 bindings for Lua.

libgit2 version
---------------

Currently supports version v0.17.0

Installing
----------

### Install lua-git2:

	luarocks install https://raw.github.com/libgit2/luagit2/master/lua-git2-scm-0.rockspec


To re-generating the bindings
-----------------------------

You will need to install LuaNativeObjects and set the CMake variable `USE_PRE_GENERATED_BINDINGS` to FALSE.
By default CMake will use the pre-generated bindings that are include in the project.

Build Dependencies
------------------

Optional dependency for re-generating Lua bindings from `*.nobj.lua` files:

* [LuaNativeObjects](https://github.com/Neopallium/LuaNativeObjects), this is the bindings generator used to convert the `*.nobj.lua` files into a native Lua module.

