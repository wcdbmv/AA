cmake_minimum_required(VERSION 3.15)
project(lab03)

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
)

set(
	HEADERS
	sort/sort.hpp
)

add_executable(            sort             main.cpp ${SOURCES} ${HEADERS})
add_executable( functional_test  functional_test.cpp ${SOURCES} ${HEADERS})
add_executable(performance_test performance_test.cpp ${SOURCES} ${HEADERS})

target_link_libraries(functional_test gtest gtest_main)
target_link_libraries(functional_test ${GTEST_LIBRARIES} Threads::Threads)
