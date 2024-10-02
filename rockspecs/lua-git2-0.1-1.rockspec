#!/usr/bin/env lua

package	= 'lua-git2'
version	= '0.1-1'
source	= {
	url	= 'git://github.com/libgit2/luagit2.git',
  branch = "v0.1"
}
description	= {
	summary	= "LibGit2 bindings for Lua.",
	detailed	= '',
	homepage	= 'https://github.com/libgit2/luagit2',
	license	= 'MIT',
	maintainer = "Robert G. Jakabosky",
}
dependencies = {
	'lua >= 5.1, < 5.5',
}
external_dependencies = {
	GIT2 = {
		header = "git2.h",
		library = "git2",
	}
}
build	= {
	type = "builtin",
	modules = {
		git2 = {
			sources = { "src/pre_generated-git2.nobj.c" },
			libraries = { "git2" },
			incdirs = { "$(GIT2_INCDIR)" },
			libdirs = { "$(GIT2_LIBDIR)" },
		}
	}
}
