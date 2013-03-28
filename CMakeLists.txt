cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(tinydir C)

#CMAKE_BUILD_TOOL

################################
# set lib version here

set(GENERIC_LIB_VERSION "1.0.0")
set(GENERIC_LIB_SOVERSION "1")


################################
# Add definitions

if(MSVC)
	add_definitions(-W4 -WX)
else(MSVC)
	add_definitions(-fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)
endif(MSVC)

################################
# Add targets
add_executable(iterate_sample iterate_sample.c)
add_executable(random_access_sample random_access_sample.c)
add_executable(interactive_sample interactive_sample.c)
