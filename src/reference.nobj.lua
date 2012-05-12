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

object "Reference" {
	basetype "git_rtype"   "integer",
	c_source [[
typedef git_reference Reference;
]],
	constructor "lookup" {
		c_call { "GitError", "err" } "git_reference_lookup"
			{ "Reference *", "&this>1", "Repository *", "repo", "const char *", "name" },
	},
	method "oid" {
		c_method_call "*OID" "git_reference_oid" {}
	},
	method "set_oid" {
		c_method_call "GitError" "git_reference_set_oid" { "OID", "&oid" }
	},
	method "target" {
		c_method_call "const char *" "git_reference_target" {}
	},
	method "set_target" {
		c_method_call "GitError" "git_reference_set_target" { "const char *", "target" }
	},
	method "type" {
		c_method_call "git_rtype" "git_reference_type" {}
	},
	method "name" {
		c_method_call "const char *" "git_reference_name" {}
	},
	method "resolve" {
		c_call "GitError" "git_reference_resolve"
			{ "Reference *", "&resolved_ref>1", "Reference *", "this" }
	},
	method "owner" {
		c_method_call "Repository *" "git_reference_owner" {}
	},
	method "rename" {
		c_method_call "GitError" "git_reference_rename" { "const char *", "new_name", "bool", "force" }
	},
	method "delete" {
		c_method_call "GitError" "git_reference_delete" {}
	},
	c_function "packall" {
		c_call "GitError" "git_reference_packall" { "Repository *", "repo" }
	},
	c_function "listall" {
		var_in{ "Repository *", "repo" },
		var_in{ "unsigned int", "list_flags" },
		var_out{ "StrArray *", "array" },
		var_out{ "GitError", "err" },
		c_source "pre" [[
	git_strarray tmp_array = { .strings = NULL, .count = 0 };
]],
		c_source[[
	/* push this onto stack now, just encase there is a out-of-memory error. */
	${array} = obj_type_StrArray_push(L, &tmp_array);
	${err} = git_reference_listall(${array}, ${repo}, ${list_flags});
	if(${err} == GIT_SUCCESS) {
		return 1; /* array is already on the stack. */
	} else {
		/* there is an error remove the temp array from stack. */
		lua_pop(L, 1);
		${array} = NULL;
	}
]]
	}
}

