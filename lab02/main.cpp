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
	std::cout <<
		"Choose algorithm:\n"
		"1. product\n"
		"2. bad::coppersmith_winograd_product\n"
		"3. good::coppersmith_winograd_product\n"
		"\n"
		">>> ";

	int algorithm_number;
	std::cin >> algorithm_number;
	product_func_type* product_func;
	switch (algorithm_number) {
	case 1:
		product_func = product;
		break;
	case 2:
		product_func = bad::coppersmith_winograd_product;
		break;
	case 3:
		product_func = good::coppersmith_winograd_product;
		break;
	default:
		std::cerr << "Wrong input\n";
		return EXIT_FAILURE;
	}

	std::cout << "\nMatrix 1\n";
	const auto m1 = input_matrix();

	std::cout << "\nMatrix 2\n";
	const auto m2 = input_matrix();

	matrix_t result;
	try {
		result = product_func(m1, m2);
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
