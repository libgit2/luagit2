#
# Lua Native Objects
#
macro(GenLuaNativeObjects _src_files_var)
	set(_new_src_files)
	foreach(_src_file ${${_src_files_var}})
		if(_src_file MATCHES ".nobj.lua")
			string(REGEX REPLACE ".nobj.lua" ".nobj.c" _src_file_out ${_src_file})
			string(REGEX REPLACE ".nobj.lua" ".nobj.h" _header_file_out ${_src_file})
			add_custom_command(OUTPUT ${_src_file_out} ${_header_file_out}
				COMMAND lua ${LUA_NATIVE_OBJECTS_PATH}/native_objects.lua -outpath ${CMAKE_CURRENT_BINARY_DIR} -gen lua ${_src_file}
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
				DEPENDS ${_src_file}
			)
			set_source_files_properties(${_src_file_out} PROPERTIES GENERATED TRUE)
			set_source_files_properties(${_header_file_out} PROPERTIES GENERATED TRUE)
			set(_new_src_files ${_new_src_files} ${_src_file_out})
		else(_src_file MATCHES ".nobj.lua")
			set(_new_src_files ${_new_src_files} ${_src_file})
		endif(_src_file MATCHES ".nobj.lua")
	endforeach(_src_file)
	set(${_src_files_var} ${_new_src_files})
endmacro(GenLuaNativeObjects _src_files_var)

