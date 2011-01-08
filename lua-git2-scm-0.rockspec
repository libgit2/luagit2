#!/usr/bin/env lua

package	= 'luagit2'
version	= 'scm-0'
source	= {
	url	= 'git://github.com/Neopallium/luagit2.git'
}
description	= {
	summary	= "LibGit2 bindings for Lua.",
	detailed	= '',
	homepage	= 'https://github.com/Neopallium/luagit2',
	license	= 'MIT',
	maintainer = "Robert G. Jakabosky",
}
dependencies = {
	'lua >= 5.1',
}
external_dependencies = {
	GIT2 = {
		header = { "git2.h" },
		library = { "git2" },
	}
}
build	= {
	type = "builtin",
	modules = {
		git2 = {
			sources = { "pre_generated-git2.nobj.c" },
			libraries = { "git2" },
		}
--[[
	type		= 'cmake',
	variables = {
		INSTALL_CMOD = "$(LIBDIR)",
		CMAKE_BUILD_TYPE = "$(CMAKE_BUILD_TYPE)",
		["CFLAGS:STRING"] = "$(CFLAGS)",
	},
--]]
}
