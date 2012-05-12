-- Copyright (c) 2010 by Robert G. Jakabosky <bobby@sharedrealm.com>
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

object "Repository" {
	c_source [[
typedef git_repository Repository;
]],
	constructor "open" {
		c_call { "GitError", "err" } "git_repository_open"
			{ "Repository *", "&this>1", "const char *", "path" },
	},
	--[=[
	constructor "discover" {
		c_source[[
	]],
		c_call { "GitError", "err" } "git_repository_open"
			{ "Repository *", "&this>1", "const char *", "path" },
	},
	--]=]
	constructor "init" {
		c_call { "GitError", "err" } "git_repository_init"
			{ "Repository *", "&this>1", "const char *", "path", "unsigned int", "is_bare" },
	},
	destructor {
		c_method_call "void"  "git_repository_free" {}
	},
	method "head" {
		c_call { "GitError", "err" } "git_repository_head"
			{ "!Reference *", "&head>1", "Repository *", "this" },
	},
	method "head_detached" {
		c_method_call "bool" "git_repository_head_detached" {}
	},
	method "head_orphan" {
		c_method_call "bool" "git_repository_head_orphan" {}
	},
	method "is_empty" {
		c_method_call "bool" "git_repository_is_empty" {}
	},
	method "is_bare" {
		c_method_call "bool" "git_repository_is_bare" {}
	},
	method "path" {
		c_method_call "const char *" "git_repository_path" {}
	},
	method "workdir" {
		c_method_call "const char *" "git_repository_workdir" {}
	},
	method "set_workdir" {
		c_method_call "GitError" "git_repository_set_workdir" { "const char *", "workdir"}
	},
	method "config" {
		c_call { "GitError", "err" } "git_repository_config"
			{ "!Config *", "&config>1", "Repository *", "this" },
	},
	method "set_config" {
		c_method_call "void" "git_repository_set_config" { "Config *", "config"}
	},
	method "odb" {
		c_call { "GitError", "err" } "git_repository_odb"
			{ "!ODB *", "&odb>1", "Repository *", "this" },
	},
	method "set_odb" {
		c_method_call "void" "git_repository_set_odb" { "ODB *", "odb"}
	},
	method "index" {
		c_call { "GitError", "err" } "git_repository_index"
			{ "!Index *", "&index>1", "Repository *", "this" },
	},
	method "set_index" {
		c_method_call "void" "git_repository_set_index" { "Index *", "index"}
	},
}

