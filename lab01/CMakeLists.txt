cmake_minimum_required(VERSION 3.14)
project(lab01)

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
	levenshtein/detail.cpp
	levenshtein/levenshtein_damerau.cpp
	levenshtein/levenshtein_matrix.cpp
	levenshtein/levenshtein_recursive.cpp
)

set(
	HEADERS
	levenshtein/levenshtein.hpp
	levenshtein/detail.hpp
)

add_executable(levenshtein main.cpp ${SOURCES} ${HEADERS})
add_executable(test        test.cpp ${SOURCES} ${HEADERS})
