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
	constructor "lookup" {
		c_call { "GitError", "err" } "git_tag_lookup"
			{ "Tag *", "&this>1", "Repository *", "repo", "OID", "&id" },
	},
	method "target" {
		c_call "GitError" "git_tag_target" { "Object *", "&out>1", "Tag *", "this" }
	},
	method "name" {
		c_method_call "const char *" "git_tag_name" {}
	},
	method "tagger" {
		c_method_call "const Signature *" "git_tag_tagger" {}
	},
	method "message" {
		c_method_call "const char *" "git_tag_message" {}
	},
}

