#include <iomanip>
#include <iostream>
#include "matrix/matrix.hpp"

matrix_t input_matrix() {
	std::cout << "height width: ";
	size_t height, width;
	std::cin >> height >> width;

	std::cout << "Input " << height << " * " << width << " elements: ";
	auto matrix = create_matrix(height, width);
	for (size_t i = 0; i != height; ++i) {
		for (size_t j = 0; j != width; ++j) {
			std::cin >> matrix[i][j];
		}
	}

	return matrix;
}

int main() {
	std::cout << "Matrix 1\n";
	const auto m1 = input_matrix();

	std::cout << "\nMatrix 2\n";
	const auto m2 = input_matrix();

	std::cout << "\nThread count\n>>> ";
	size_t thread_count;
	std::cin >> thread_count;

	matrix_t result;
	try {
		result = coppersmith_winograd_product(m1, m2, thread_count);
	} catch(...) {
		std::cout << "\nWrong matrix sizes\n";
		return EXIT_FAILURE;
	};

	std::cout << "\nResult:\n";
	for (size_t i = 0; i != result.size(); ++i) {
		for (size_t j = 0; j != result[i].size(); ++j) {
			std::cout << std::setw(10) << result[i][j];
		}
		std::cout << '\n';
	}
}
