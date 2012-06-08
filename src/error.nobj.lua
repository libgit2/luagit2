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

-- Convert Git Error codes into strings.
error_code "GitError" "int" {
	is_error_check = function(rec) return "(GIT_OK != ${" .. rec.name .. "})" end,
	default = "GIT_OK",
	c_source [[
	const git_error *giterr;
	switch(err) {
	case GIT_ERROR:
		giterr = giterr_last();
		err_str = giterr->message;
		break;
	case GIT_ENOTFOUND:
		err_str = "ENOTFOUND";
		break;
	case GIT_EEXISTS:
		err_str = "EEXISTS";
		break;
	case GIT_EAMBIGUOUS:
		err_str = "EAMBIGUOUS";
		break;
	case GIT_EBUFS:
		err_str = "EBUFS";
		break;
	case GIT_PASSTHROUGH:
		err_str = "PASSTHROUGH";
		break;
	case GIT_REVWALKOVER:
		err_str = "REVWALKOVER";
		break;
	case GIT_OK:
	default:
		break;
	}
]],
}

