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
typedef git_commit Commit;
]]

object "Commit" {
	extends "Object",
	constructor "new" {
		var_in{"Repository *", "repo"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_commit_new(&(${this}), ${repo});
]],
	},
	constructor "lookup" {
		var_in{"Repository *", "repo"},
		var_in{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_commit_lookup(&(${this}), ${repo}, &(${id}));
]],
	},
	method "message" {
		c_call "const char *"  "git_commit_message" {}
	},
	method "message_short" {
		c_call "const char *"  "git_commit_message_short" {}
	},
	method "set_message" {
		c_call "void"  "git_commit_set_message" { "const char *", "message" }
	},
	method "time" {
		c_call "time_t"  "git_commit_time" {}
	},
	method "committer" {
		c_call "const Signature *"  "git_commit_committer" {}
	},
	method "set_committer" {
		c_call "void"  "git_commit_set_committer" { "const Signature *", "sig" }
	},
	method "author" {
		c_call "const Signature *"  "git_commit_author" {}
	},
	method "set_author" {
		c_call "void"  "git_commit_set_author" { "const Signature *", "sig" }
	},
	method "tree" {
		c_call "const Tree *"  "git_commit_tree" {}
	},
	method "set_tree" {
		c_call "void"  "git_commit_set_tree" { "Tree *", "tree" }
	},
	method "parentcount" {
		c_call "unsigned int"  "git_commit_parentcount" {}
	},
	method "parent" {
		c_call "Commit *"  "git_commit_parent" { "unsigned int", "n" }
	},
	method "add_parent" {
		c_call "GitError"  "git_commit_add_parent" { "Commit *", "parent" }
	},
}

