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

object "Tag" {
	c_source [[
typedef git_tag Tag;
]],
	extends "Object",
	constructor "new" {
		var_in{"Repository *", "repo"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_tag_new(&(${this}), ${repo});
]],
	},
	constructor "lookup" {
		var_in{"Repository *", "repo"},
		var_in{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_tag_lookup(&(${this}), ${repo}, &(${id}));
]],
	},
	method "target" {
		c_call "const Object *" "git_tag_target" {}
	},
	method "set_target" {
		c_call "void" "git_tag_set_target" { "Object *", "target" }
	},
	method "name" {
		c_call "const char *" "git_tag_name" {}
	},
	method "set_name" {
		c_call "void" "git_tag_set_name" { "const char *", "name" }
	},
	method "tagger" {
		c_call "const Signature *" "git_tag_tagger" {}
	},
	method "set_tagger" {
		c_call "void" "git_tag_set_tagger" { "const Signature *", "tagger" }
	},
	method "message" {
		c_call "const char *" "git_tag_message" {}
	},
	method "set_message" {
		c_call "void" "git_tag_set_message" { "const char *", "message" }
	},
}

