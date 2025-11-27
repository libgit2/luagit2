local git_ref = '$git_ref'
local modrev = '$modrev'
local specrev = '$specrev'

local repo_url = '$repo_url'

rockspec_format = '3.0'
package = '$package'
version = modrev ..'-'.. specrev

description = {
  summary = '$summary',
  detailed = $detailed_description,
  labels = $labels,
  homepage = '$homepage',
  $license
}

dependencies = $dependencies

test_dependencies = $test_dependencies

source = {
  url = repo_url .. '/archive/' .. git_ref .. '.zip',
  dir = '$repo_name-' .. '$archive_dir_suffix',
}

if modrev == 'scm' or modrev == 'dev' then
  source = {
    url = repo_url:gsub('https', 'git')
  }
end

external_dependencies = {
	GIT2 = {
		header = "git2.h",
		library = "git2",
	}
}
build	= {
	type = "builtin",
	modules = {
		git2 = {
			sources = { "src/pre_generated-git2.nobj.c" },
			libraries = { "git2" },
			incdirs = { "$(GIT2_INCDIR)" },
			libdirs = { "$(GIT2_LIBDIR)" },
		}
	}
}
