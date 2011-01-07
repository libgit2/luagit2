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

c_source [[
typedef git_revwalk RevWalk;
]]

object "RevWalk" {
	extends "Object",
	constructor "new" {
		var_in{"Repository *", "repo"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_revwalk_new(&(${this}), ${repo});
]],
	},
	destructor {
		c_call "void" "git_revwalk_free" {}
	},
	method "reset" {
		c_call "void" "git_revwalk_reset" {}
	},
	method "push" {
		c_call "GitError" "git_revwalk_push" { "Commit *", "commit" }
	},
	method "hide" {
		c_call "GitError" "git_revwalk_hide" { "Commit *", "commit" }
	},
	method "next" {
		c_call "Commit *" "git_revwalk_next" {}
	},
	method "sorting" {
		c_call "GitError" "git_revwalk_sorting" { "unsigned int", "sort_mode" }
	},
	method "repository" {
		c_call "Repository *" "git_revwalk_repository" {}
	},
}

