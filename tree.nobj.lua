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
typedef git_tree Tree;
]]

object "Tree" {
	extends "Object",
	constructor "new" {
		var_in{"Repository *", "repo"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_tree_new(&(${this}), ${repo});
]],
	},
	constructor "lookup" {
		var_in{"Repository *", "repo"},
		var_in{"OID", "id"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_tree_lookup(&(${this}), ${repo}, &(${id}));
]],
	},
	method "entrycount" {
		c_call "size_t"  "git_tree_entrycount" {}
	},
	method "entry_byname" {
		c_call "TreeEntry *"  "git_tree_entry_byname" { "const char *", "filename" }
	},
	method "entry_byindex" {
		c_call "TreeEntry *"  "git_tree_entry_byindex" { "int", "index" }
	},
	method "add_entry" {
		var_in{"const OID", "id"},
		var_in{"const char *", "filename"},
		var_in{"int", "attributes"},
		var_out{"GitError", "err"},
		c_source [[
	${err} = git_tree_add_entry(${this}, &(${id}), ${filename}, ${attributes});
]],
	},
	method "remove_entry_byname" {
		c_call "GitError"  "git_tree_remove_entry_byname" { "const char *", "filename" }
	},
	method "remove_entry_byindex" {
		c_call "GitError"  "git_tree_remove_entry_byindex" { "int", "index" }
	},
}

