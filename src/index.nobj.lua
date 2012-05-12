-- Copyright (c) 2010-2012 by Robert G. Jakabosky <bobby@sharedrealm.com>
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

object "Index" {
	c_source [[
typedef git_index Index;
]],
	constructor "bare" {
		c_call {"GitError", "err"} "git_index_open"
			{ "Index *", "&this", "const char *", "index_path" },
	},
	destructor {
		c_method_call "void"  "git_index_free" {}
	},
	method "clear" {
		c_method_call "void"  "git_index_clear" {}
	},
	method "read" {
		c_method_call "GitError"  "git_index_read" {}
	},
	method "write" {
		c_method_call "GitError"  "git_index_write" {}
	},
	method "find" {
		c_method_call "int"  "git_index_find" { "const char *", "path" }
	},
	method "uniq" {
		c_method_call "void"  "git_index_uniq" {}
	},
	method "add" {
		c_method_call "GitError"  "git_index_add" { "const char *", "path", "int", "stage" }
	},
	method "add2" {
		c_method_call "GitError"  "git_index_add2" { "IndexEntry *", "source_entry" }
	},
	method "append" {
		c_method_call "GitError"  "git_index_append" { "const char *", "path", "int", "stage" }
	},
	method "append2" {
		c_method_call "GitError"  "git_index_append2" { "IndexEntry *", "source_entry" }
	},
	method "remove" {
		c_method_call "GitError"  "git_index_remove" { "int", "position" }
	},
	method "get" {
		c_method_call "IndexEntry *"  "git_index_get" { "int", "n" }
	},
	method "entrycount" {
		c_method_call "unsigned int"  "git_index_entrycount" {}
	},
	method "entrycount_unmerged" {
		c_method_call "unsigned int"  "git_index_entrycount_unmerged" {}
	},
	method "get_unmerged_bypath" {
		c_method_call "const IndexEntryUnmerged *"  "git_index_get_unmerged_bypath" { "const char *", "path" }
	},
	method "get_unmerged_byindex" {
		c_method_call "const IndexEntryUnmerged *"  "git_index_get_unmerged_byindex" { "int", "n" }
	},
	method "read_tree" {
		c_method_call "GitError"  "git_index_read_tree" { "Tree *", "tree" }
	},
}

