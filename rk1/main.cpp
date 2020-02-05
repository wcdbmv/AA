#include <iostream>
#include "sparse_matrix/sparse_matrix.hpp"

int main() {
	SparseMatrix<int> a(2, 2);
	a.append(1, 1, 1);
	a.append(1, 0, 2);
	a.append(0, 1, 3);
	a.append(0, 0, 4);
	std::cout << "a:\n" << a;
	a.sort();
	std::cout << "after sort:\n" << a;
}
