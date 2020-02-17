#include <iostream>
#include "sparse_matrix/sparse_matrix.hpp"

#define PATH_PREFIX "../"

int main() {
	auto a = SparseMatrix<double>::read(PATH_PREFIX "io/sm01.txt");
	auto b = SparseMatrix<double>::read(PATH_PREFIX "io/sm02.txt");
	std::cout << a + b << '\n' << a + a;
}
