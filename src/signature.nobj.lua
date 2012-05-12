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

object "Signature" {
	c_source [[
typedef git_signature Signature;
]],
	constructor "new" {
		c_call "GitError" "git_signature_new"
			{ "Signature *", "&this>1", "const char *", "name", "const char *", "email", "git_time_t", "time", "int", "offset" },
	},
	constructor "now" {
		c_call "GitError" "git_signature_now"
			{ "Signature *", "&this>1", "const char *", "name", "const char *", "email" },
	},
	destructor {
		c_method_call "void" "git_signature_free" {},
	},
	method "name" {
		var_out{"const char *", "name"},
		c_source "${name} = ${this}->name;",
	},
	method "email" {
		var_out{"const char *", "email"},
		c_source "${email} = ${this}->email;",
	},
	method "when" {
		var_out{"git_time_t", "time"},
		var_out{"int", "offset"},
		c_source "${time} = ${this}->when.time; ${offset} = ${this}->when.offset;",
	},
}

