cmake_minimum_required(VERSION 3.15)
project(lab07)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_compile_options(
	-Werror

	-Wall
	-Wextra
	-Wpedantic

	-Wcast-align
	-Wcast-qual
#	-Wconversion
#	-Wctor-dtor-privacy
	-Wenum-compare
	-Wfloat-equal
	-Wnon-virtual-dtor
	-Wold-style-cast
	-Woverloaded-virtual
	-Wredundant-decls
#	-Wsign-conversion
	-Wsign-promo
)

set(
	SOURCES
	string/search.cpp
)

set(
	HEADERS
	string/search.hpp
)

add_executable(main main.cpp ${SOURCES} ${HEADERS})
