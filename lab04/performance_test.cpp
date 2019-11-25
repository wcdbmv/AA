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

double count_time(parallel_product_func_type parallel_product_func, const matrix_t& m1, const matrix_t& m2, size_t thread_count) {
	constexpr size_t N = 5;

	const auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i != N; ++i) {
		parallel_product_func(m1, m2, thread_count);
	}
	const auto end = std::chrono::high_resolution_clock::now();

	return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1.0e9 / N;
}

void test(size_t begin, size_t end, size_t step) {
	constexpr int column_width = 20;
	const std::vector<size_t> thread_counts = {1, 2, 4, 8, 16, 32, 64};

	std::cout << "size";
	for (auto&& thread_count: thread_counts) {
		std::cout << std::setw(column_width) << thread_count;
	}
	std::cout << '\n';

	for (size_t i = begin; i <= end; i += step) {
		const auto m1 = generate_matrix(i);
		const auto m2 = generate_matrix(i);
		std::cout << std::setw(4) << i << std::fixed << std::setprecision(4);
		for (auto&& thread_count: thread_counts) {
			std::cout
				<< std::fixed
				<< std::setprecision(4)
				<< std::setw(column_width)
				<< count_time(coppersmith_winograd_product, m1, m2, thread_count);
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int main() {
	test(100, 1000, 100);
	test(101, 1001, 100);
}
