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
typedef git_index_entry IndexEntry;
]]

object "IndexEntry" {
	constructor {
		c_source [[
	${this} = calloc(1, sizeof(IndexEntry));
]],
	},
	destructor {
		c_source [[
	if(${this}->path != NULL) {
		free(${this}->path);
	}
	free(${this});
]]
	},
	method "ctime" {
		var_out{"time_t", "secs"},
		var_out{"time_t", "nanosecs"},
		c_source [[
	${secs} = ${this}->ctime.seconds;
	${nanosecs} = ${this}->ctime.nanoseconds;
]]
	},
	method "set_ctime" {
		var_in{"time_t", "secs"},
		var_in{"time_t", "nanosecs"},
		c_source [[
	${this}->ctime.seconds = ${secs};
	${this}->ctime.nanoseconds = ${nanosecs};
]]
	},
	method "mtime" {
		var_out{"time_t", "secs"},
		var_out{"time_t", "nanosecs"},
		c_source [[
	${secs} = ${this}->mtime.seconds;
	${nanosecs} = ${this}->mtime.nanoseconds;
]]
	},
	method "set_mtime" {
		var_in{"time_t", "secs"},
		var_in{"time_t", "nanosecs"},
		c_source [[
	${this}->mtime.seconds = ${secs};
	${this}->mtime.nanoseconds = ${nanosecs};
]]
	},
	method "dev" {
		var_out{"unsigned int", "ret"},
		c_source "${ret} = ${this}->dev;"
	},
	method "set_dev" {
		var_in{"unsigned int", "val"},
		c_source "${this}->dev = ${val};"
	},
	method "ino" {
		var_out{"unsigned int", "ret"},
		c_source "${ret} = ${this}->ino;"
	},
	method "set_ino" {
		var_in{"unsigned int", "val"},
		c_source "${this}->ino = ${val};"
	},
	method "mode" {
		var_out{"unsigned int", "ret"},
		c_source "${ret} = ${this}->mode;"
	},
	method "set_mode" {
		var_in{"unsigned int", "val"},
		c_source "${this}->mode = ${val};"
	},
	method "uid" {
		var_out{"unsigned int", "ret"},
		c_source "${ret} = ${this}->uid;"
	},
	method "set_uid" {
		var_in{"unsigned int", "val"},
		c_source "${this}->uid = ${val};"
	},
	method "gid" {
		var_out{"unsigned int", "ret"},
		c_source "${ret} = ${this}->gid;"
	},
	method "set_gid" {
		var_in{"unsigned int", "val"},
		c_source "${this}->gid = ${val};"
	},
	method "file_size" {
		var_out{"off_t", "ret"},
		c_source "${ret} = ${this}->file_size;"
	},
	method "set_file_size" {
		var_in{"off_t", "val"},
		c_source "${this}->file_size = ${val};"
	},
	method "id" {
		var_out{"OID", "ret"},
		c_source "${ret} = ${this}->oid;"
	},
	method "set_id" {
		var_in{"OID", "val"},
		c_source "${this}->oid = ${val};"
	},
	method "flags" {
		var_out{"unsigned short", "ret"},
		c_source "${ret} = ${this}->flags;"
	},
	method "set_flags" {
		var_in{"unsigned short", "val"},
		c_source "${this}->flags = ${val};"
	},
	method "flags_extended" {
		var_out{"unsigned short", "ret"},
		c_source "${ret} = ${this}->flags_extended;"
	},
	method "set_flags_extended" {
		var_in{"unsigned short", "val"},
		c_source "${this}->flags_extended = ${val};"
	},
	method "path" {
		var_out{"const char *", "ret"},
		c_source "${ret} = ${this}->path;"
	},
	method "set_path" {
		var_in{"const char *", "val"},
		c_source [[
	if(${this}->path != NULL) {
		free(${this}->path);
	}
	${this}->path = strndup(${val}, ${val}_len);
]]
	},
}

