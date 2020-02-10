cmake_minimum_required(VERSION 3.15)
project(rk1)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
	-Werror

	-Wall
	-Wextra
	-Wpedantic

	-Wcast-align
	-Wcast-qual
	-Wconversion
	-Wctor-dtor-privacy
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
	HEADERS
	sparse_matrix/sparse_matrix.hpp
)

set(
	SOURCES
)

add_executable(rk1 main.cpp ${HEADERS} ${SOURCES})
