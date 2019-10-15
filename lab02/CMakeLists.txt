cmake_minimum_required(VERSION 3.15)
project(lab02)

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
	SOURCES
	matrix/matrix.cpp
)

set(
	HEADERS
	matrix/matrix.hpp
)

add_executable(matrix main.cpp ${SOURCES} ${HEADERS})
add_executable(test   test.cpp ${SOURCES} ${HEADERS})
