#
# Lua bindings for libgit2
#
cmake_minimum_required(VERSION 2.8)

project(lua-git2 C)

set(BUILD_SHARED_LIBS TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(INSTALL_CMOD share/lua/cmod CACHE PATH "Directory to install Lua binary modules (configure lua via LUA_CPATH)")
set(LUA_NATIVE_OBJECTS_PATH ../LuaNativeObjects CACHE PATH
				"Directory to LuaNativeObjects bindings generator.")
set(USE_PRE_GENERATED_BINDINGS TRUE CACHE BOOL
				"Set this to FALSE to re-generate bindings using LuaNativeObjects")

set(COMMON_CFLAGS "${CFLAGS}")
set(COMMON_LIBS)

## Lua 5.1.x
include(FindLua51)
if(NOT ${LUA51_FOUND})
    message(FATAL_ERROR "The FindLua51 module could not find lua :-(")
endif()
set(COMMON_LIBS "${COMMON_LIBS};${LUA_LIBRARIES}")
include_directories(${LUA_INCLUDE_DIR})

## LibGit2
include(FindPkgConfig)
pkg_search_module(GIT2 REQUIRED libgit2=0.17.0)
add_definitions(${GIT2_CFLAGS})
link_directories(${GIT2_LIBRARY_DIRS})
include_directories(${GIT2_INCLUDE_DIRS})
set(COMMON_LIBS "${COMMON_LIBS};${GIT2_LIBRARIES}")

## LuaNativeObjects
include(LuaNativeObjects)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR})

#
# Setup CMAKE_C_FLAGS* and CMAKE_CXX_FLAGS*
#
if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -Wall -Wextra -Wshadow -W -pedantic -std=gnu99 -fgnu89-inline")
	set(CMAKE_C_FLAGS_RELEASE        "${CMAKE_C_FLAGS_RELEASE}     -O3 -march=native -g")
	set(CMAKE_C_FLAGS_DEBUG          "${CMAKE_C_FLAGS_DEBUG}       -O0 -g")
	set(CMAKE_C_FLAGS_PROFILE        "${CMAKE_C_FLAGS_PROFILE}     -O2 -g -DNDEBUG")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_WITHDEBINFO} -O2 -g")
endif(CMAKE_COMPILER_IS_GNUCC)

## LuaGit2
set(LUA_GIT2_SRC
	git2.nobj.lua
)

if(${USE_PRE_GENERATED_BINDINGS})
	set(LUA_GIT2_SRC src/pre_generated-git2.nobj.c)
else()
	# Generate Lua bindings.
	GenLuaNativeObjects(LUA_GIT2_SRC)
endif()

add_library(lua-git2 MODULE ${LUA_GIT2_SRC})
target_link_libraries(lua-git2 ${COMMON_LIBS})
set_target_properties(lua-git2 PROPERTIES PREFIX "")
set_target_properties(lua-git2 PROPERTIES COMPILE_FLAGS "${COMMON_CFLAGS}")
set_target_properties(lua-git2 PROPERTIES OUTPUT_NAME git2)

install(TARGETS lua-git2
        DESTINATION "${INSTALL_CMOD}")

