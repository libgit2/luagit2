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

object "IndexEntry" {
	c_source [[
typedef git_index_entry IndexEntry;
]],
	constants {
		NAMEMASK		= 0x0fff,
		STAGEMASK		= 0x3000,
		EXTENDED		= 0x4000,
		VALID				= 0x8000,
		STAGESHIFT  = 12,
	},
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
	method "stage" {
		c_method_call "int" "git_index_entry_stage" {},
	},
	method "ctime" {
		var_out{"git_time_t", "secs"},
		var_out{"unsigned int", "nanosecs"},
		c_source [[
	${secs} = ${this}->ctime.seconds;
	${nanosecs} = ${this}->ctime.nanoseconds;
]]
	},
	method "set_ctime" {
		var_in{"git_time_t", "secs"},
		var_in{"unsigned int", "nanosecs"},
		c_source [[
	${this}->ctime.seconds = ${secs};
	${this}->ctime.nanoseconds = ${nanosecs};
]]
	},
	method "mtime" {
		var_out{"git_time_t", "secs"},
		var_out{"unsigned int", "nanosecs"},
		c_source [[
	${secs} = ${this}->mtime.seconds;
	${nanosecs} = ${this}->mtime.nanoseconds;
]]
	},
	method "set_mtime" {
		var_in{"git_time_t", "secs"},
		var_in{"unsigned int", "nanosecs"},
		c_source [[
	${this}->mtime.seconds = ${secs};
	${this}->mtime.nanoseconds = ${nanosecs};
]]
	},
	field "unsigned int" "dev",
	field "unsigned int" "ino",
	field "unsigned int" "mode",
	field "unsigned int" "uid",
	field "unsigned int" "gid",
	field "off_t" "file_size",
	field "OID" "oid",
	field "unsigned int" "flags",
	field "unsigned int" "flags_extended",
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
	${this}->path = malloc(${val_len});
	strncpy(${this}->path, ${val}, ${val_len});
	${this}->path[${val_len}] = 0;
]]
	},
}

