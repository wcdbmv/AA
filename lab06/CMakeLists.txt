cmake_minimum_required(VERSION 3.15)
project(lab06)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_compile_options(
	-Werror

	-Wall
	-Wextra
	-Wpedantic

	-Wcast-align
	-Wcast-qual
	-Wconversion
#	-Wctor-dtor-privacy
	-Wenum-compare
	-Wfloat-equal
	-Wnon-virtual-dtor
	-Wold-style-cast
	-Woverloaded-virtual
	-Wredundant-decls
	-Wsign-conversion
	-Wsign-promo
)

set(
	SOURCES
	algs/colony.cpp
	algs/exhaustive_search.cpp
	graph/graph.cpp
)

set(
	HEADERS
	algs/colony.hpp
	algs/exhaustive_search.hpp
	graph/graph.hpp
)

add_executable(main main.cpp ${SOURCES} ${HEADERS})
