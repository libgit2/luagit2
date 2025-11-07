luagit2
=======

LibGit2 bindings for Lua. [API Docs](http://libgit2.github.io/luagit2/)

libgit2 version
---------------

Currently supports version >= 0.17

Installing
----------

### Install lua-git2 release 0.1:

	luarocks install lua-git2


### Install lua-git2 from github:

	luarocks install https://raw.githubusercontent.com/libgit2/luagit2/refs/heads/master/rockspecs/lua-git2-scm-0.rockspec


To re-generating the bindings
-----------------------------

You will need to install LuaNativeObjects and set the CMake variable `USE_PRE_GENERATED_BINDINGS` to FALSE.
By default CMake will use the pre-generated bindings that are include in the project.

Build Dependencies
------------------

Optional dependencies for re-generating Lua bindings from `*.nobj.lua` files:

* [LuaNativeObjects](https://github.com/Neopallium/LuaNativeObjects), this is the bindings generator used to convert the `*.nobj.lua` files into a native Lua module. To use it, there are two options:
	- clone the repository to ../LuaNativeObjects; or
	- install the LuaRocks packages:
		- `luanativeobjects`
		- `luanativeobjects-luadoc` (only if also generating docs)
- [`lua-json`](https://github.com/neoxic/lua-json)

Optional dependency for generating docs:

- [`ldoc`](https://lunarmodules.github.io/ldoc/)

