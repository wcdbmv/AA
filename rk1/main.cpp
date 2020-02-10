#include <iostream>
#include "sparse_matrix/sparse_matrix.hpp"

int main() {
	SparseMatrix<int> a(2, 2);
	a.append(1, 1, 1);
	a.append(1, 0, 2);
	a.append(0, 1, 3);
	a.append(0, 0, 4);
	a.sort();
	std::cout << "a:\n" << a;
	std::cout << "RRCU a:\n";
	a.RRCU(std::cout);
	SparseMatrix<int> b(2, 2);
	b.append(1, 1, 1);
	b.append(1, 0, 2);
	b.append(0, 1, 3);
	b.append(0, 0, 4);
	b.sort();
	std::cout << "b:\n" << b;
	std::cout << "RRCU b:\n";
	b.RRCU(std::cout);
	SparseMatrix<int> c(2, 2);
	c.append(1, 1, 4);
	c.append(1, 0, 3);
	c.append(0, 1, 2);
	c.append(0, 0, 1);
	c.sort();
	std::cout << "c:\n" << c;
	std::cout << "RRCU c:\n";
	c.RRCU(std::cout);
	std::cout << "a + b\n" << a + b;

	SparseMatrix<int> d = a * b;
	std::cout << "d:\n" << d;
	SparseMatrix<int> e = a * c;
	std::cout << "e:\n" << e;

	SparseMatrix<int> sm1(4, 3);
	sm1.append(0, 0, 3);
	sm1.append(2, 2, 5);
	std::cout << "RRCU sm1:\n";
	sm1.RRCU(std::cout);
	SparseMatrix<int> sm2(3, 4);
	sm2.append(0, 1, 1);
	sm2.append(2, 0, 2);
	sm2.append(2, 2, 4);
	std::cout << "RRCU sm2:\n";
	sm2.RRCU(std::cout);
	SparseMatrix<int> sm = sm1 * sm2;
	std::cout << "sm:\n" << sm;

	/*
	SparseMatrix<int> r(5, 5);
	r.append(0, 0, 1);
	r.append(0, 1, -1);
	r.append(0, 3, -3);
	r.append(1, 0, -2);
	r.append(1, 1, 5);
	r.append(2, 2, 4);
	r.append(2, 3, 6);
	r.append(2, 4, 4);
	r.append(3, 0, -4);
	r.append(3, 2, 2);
	r.append(3, 3, 7);
	r.append(4, 2, 8);
	r.append(4, 4, -5);
	std::cout << "RRCU r:\n";
	r.RRCU(std::cout);

	SparseMatrix<int> sm(3, 3);
	sm.append(0, 0, 3);
	sm.append(2, 2, 5);
	std::cout << "RRCU sm:\n";
	sm.RRCU(std::cout);
	*/
}
