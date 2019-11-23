#include <random>
#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>
#include "matrix/matrix.hpp"

int dont_try_to_guess() {
	static thread_local std::mt19937 generator(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> distribution(-1000, 1000);
	return distribution(generator);
}

matrix_t generate_matrix(size_t size) {
	auto matrix = create_matrix(size, size);

	for (size_t i = 0; i != size; ++i) {
		for (size_t j = 0; j != size; ++j) {
			matrix[i][j] = dont_try_to_guess();
		}
	}

	return matrix;
}

double count_time(product_func_type product_func, const matrix_t& m1, const matrix_t& m2) {
	constexpr size_t N = 1;

	const auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i != N; ++i) {
		product_func(m1, m2);
	}
	const auto end = std::chrono::high_resolution_clock::now();

	return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1.0e6 / N;
}

void test(size_t begin, size_t end, size_t step) {
	constexpr int column_width = 20;
	std::cout << "size" << std::setw(column_width) << "product" << std::setw(column_width) << "bad::winograd" << std::setw(column_width) << "good::winograd\n";
	for (size_t i = begin; i <= end; i += step) {
		const auto m1 = generate_matrix(i);
		const auto m2 = generate_matrix(i);
		std::cout
			<< std::setw(4) << i
			<< std::fixed << std::setprecision(8)
			<< std::setw(column_width) << count_time(product, m1, m2)
			<< std::setw(column_width) << count_time(bad::coppersmith_winograd_product, m1, m2)
			<< std::setw(column_width) << count_time(good::coppersmith_winograd_product, m1, m2) << '\n';
	}
	std::cout << '\n';
}

int main() {
	test(100, 1000, 100);
	test(101, 1001, 100);
}
