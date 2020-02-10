cmake_minimum_required(VERSION 3.14)
project(lab01)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

include_directories(.)
include_directories(/usr/src/googletest/googletest/include)

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
	-Wsign-conversion
	-Wsign-promo
)

set(
	SOURCES
	levenshtein/core/levenshtein_core_damerau_matrix.cpp
	levenshtein/core/levenshtein_core_damerau_recursive.cpp
	levenshtein/core/levenshtein_core_detail_matrix.cpp
	levenshtein/core/levenshtein_core_matrix.cpp
	levenshtein/levenshtein_damerau_matrix.cpp
	levenshtein/levenshtein_damerau_recursive.cpp
	levenshtein/levenshtein_detail_matrix.cpp
	levenshtein/levenshtein_matrix.cpp
)

set(
	HEADERS
	levenshtein/core/levenshtein_core_detail_matrix.hpp
	levenshtein/core/levenshtein_core.hpp
	levenshtein/levenshtein.hpp
	levenshtein/levenshtein_detail_matrix.hpp
)

add_executable(     levenshtein             main.cpp ${SOURCES} ${HEADERS})
add_executable( functional_test  functional_test.cpp ${SOURCES} ${HEADERS})
add_executable(performance_test performance_test.cpp ${SOURCES} ${HEADERS})

target_link_libraries(functional_test gtest gtest_main)
target_link_libraries(functional_test ${GTEST_LIBRARIES} Threads::Threads)
