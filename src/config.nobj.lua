-- Copyright (c) 2012 by Robert G. Jakabosky <bobby@sharedrealm.com>
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

object "Config" {
	c_source [[
typedef git_config Config;
]],
	constructor "new" {
		c_call { "GitError", "err"} "git_config_new" { "Config *", "&this" },
	},
	constructor "open" {
		c_call { "GitError", "err"} "git_config_open_ondisk"
			{ "Config *", "&this", "const char *", "path" },
	},
	destructor "free" {
		c_method_call "void" "git_config_free" {},
	},
	method "add_file_ondisk" {
		c_method_call { "GitError", "err"} "git_config_add_file_ondisk"
			{ "const char *", "path", "int", "priority" },
	},
	method "get_int32" {
		c_method_call { "GitError", "err"} "git_config_get_int32"
			{ "const char *", "name", "int32_t>1", "&out" },
	},
	method "set_int32" {
		c_method_call { "GitError", "err"} "git_config_set_int32"
			{ "const char *", "name", "int32_t", "value" },
	},
	method "get_int64" {
		c_method_call { "GitError", "err"} "git_config_get_int64"
			{ "const char *", "name", "int64_t>1", "&out" },
	},
	method "set_int64" {
		c_method_call { "GitError", "err"} "git_config_set_int64"
			{ "const char *", "name", "int64_t", "value" },
	},
	method "get_bool" {
		var_out{"bool", "out"},
		c_method_call { "GitError", "err"} "git_config_get_bool"
			{ "const char *", "name", "int", "(&out_int)" },
		c_source[[
	${out} = ${out_int};
]],
	},
	method "set_bool" {
		var_in{"bool", "value"},
		c_source[[
	${value_int} = ${value} ? 1 : 0;
]],
		c_method_call { "GitError", "err"} "git_config_set_bool"
			{ "const char *", "name", "int", "(value_int)" },
	},
	method "get_string" {
		c_method_call { "GitError", "err"} "git_config_get_string"
			{ "const char *", "name", "const char *>1", "&out" },
	},
	method "set_string" {
		c_method_call { "GitError", "err"} "git_config_set_string"
			{ "const char *", "name", "const char *", "value" },
	},
	method "delete" {
		c_method_call { "GitError", "err"} "git_config_delete" { "const char *", "name" },
	},
}

