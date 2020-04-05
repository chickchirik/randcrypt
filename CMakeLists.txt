# CMake configuraton for the whole project is defined here

cmake_minimum_required(VERSION 2.6)
project(randcrypt)

# Set root directory alias
set(ROOT_DIR "${randcrypt_SOURCE_DIR}")

# Set an output directory for our binaries
set(BIN_DIR ${randcrypt_SOURCE_DIR}/bin)

# Set alias for tests directory
set(t_DIR ${ROOT_DIR}/t)

# Set alias for source directory
set(src_DIR ${ROOT_DIR}/src)

# Set alias for dependecies directory
# set(DEP_DIR ${ROOT_DIR}/dependencies)

# Using modified CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${randcrypt_SOURCE_DIR}/cmake")

# add conan configuration
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Set compilation flags based on compiler
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++14" )
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Function recursively iterates through provided directories and creates a
# global INCLUDE_LIST variable string.
# Big thanks to Gonzalo Garramuno (https://cmake.org/pipermail/cmake/2017-October/066495.html)
function(make_include_directories_list)
	if((ARGC EQUAL 2) OR (ARGC GREATER 2))
		foreach(dir IN LISTS ARGN)
			file(GLOB_RECURSE new_list ${dir}/*.h ${dir}/*.hpp)
			set(dir_list "")
			foreach(file_path ${new_list})
				get_filename_component(dir_path ${file_path} PATH)
				set(dir_list ${dir_list} ${dir_path})
			endforeach()
			list(REMOVE_DUPLICATES dir_list)
			list(APPEND RESULT_LIST ${dir_list})
		endforeach()
		set(INCLUDE_LIST ${RESULT_LIST} PARENT_SCOPE)
	else()
		message("wrong function usage: make_include_directories_list recuires at least one argument and only one return value")
	endif()
endfunction()

# Look for all source files in subproject and save them
file(GLOB_RECURSE t_CPP ${t_DIR}/*.cpp ${t_DIR}/*.c)

# Look for all source files in src and save them
file(GLOB_RECURSE src_CPP ${src_DIR}/*.cpp ${src_DIR}/*.c)

# Look for all dynamic libraries in dependencies and save them in the list
# file(GLOB_RECURSE DEP_LIBS ${DEP_DIR}/*.dylib)

# Look for all include paths in dependencies and subprojects and include them
make_include_directories_list(${src_DIR} ${t_DIR})
include_directories(${INCLUDE_LIST} ${CONAN_INCLUDE_DIRS})
message(JOPA ${CONAN_INCLUDE_DIRS})

# Look in the subdirectories to find its CMakeLists.txt so we can build the executable
add_subdirectory(t)
