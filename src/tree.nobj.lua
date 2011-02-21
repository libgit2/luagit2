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

object "Tree" {
	c_source [[
typedef git_tree Tree;
]],
	extends "Object",
	constructor "new" {
		c_call { "GitError", "err" } "git_tree_new"
			{ "Tree *", "&this>1", "Repository *", "repo" },
	},
	constructor "lookup" {
		c_call { "GitError", "err" } "git_tree_lookup"
			{ "Tree *", "&this>1", "Repository *", "repo", "OID", "&id" },
	},
	method "entrycount" {
		c_method_call "size_t"  "git_tree_entrycount" {}
	},
	method "entry_byname" {
		c_method_call "TreeEntry *"  "git_tree_entry_byname" { "const char *", "filename" }
	},
	method "entry_byindex" {
		c_method_call "TreeEntry *"  "git_tree_entry_byindex" { "int", "index" }
	},
	method "add_entry" {
		c_method_call { "GitError", "err" } "git_tree_add_entry"
			{ "const OID", "&id", "const char *", "filename", "int", "attributes" },
	},
	method "remove_entry_byname" {
		c_method_call "GitError"  "git_tree_remove_entry_byname" { "const char *", "filename" }
	},
	method "remove_entry_byindex" {
		c_method_call "GitError"  "git_tree_remove_entry_byindex" { "int", "index" }
	},
}

