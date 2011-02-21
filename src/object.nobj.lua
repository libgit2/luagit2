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

object "Object" {
	c_source [[
typedef git_object Object;
]],
	dyn_caster {
		caster_type = "switch",
		value_function = "git_object_type",
		value_map = {
		GIT_OBJ_BLOB = "Blob",
		GIT_OBJ_COMMIT = "Commit",
		GIT_OBJ_TREE = "Tree",
		},
	},
	destructor {
		c_method_call "void" "git_object_free" {}
	},
	method "write" {
		c_method_call "GitError" "git_object_write" {}
	},
	method "id" {
		var_out{ "OID", "id" },
		c_source [[
	${id} = *(git_object_id(${this}));
]]
	},
	method "type" {
		var_out{"const char *", "type"},
		c_source "${type} = git_object_type2string(git_object_type(${this}));"
	},
	method "owner" {
		c_method_call "Repository *" "git_object_owner" {}
	},
}

