#include "detail.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>

namespace levenshtein {
inline namespace detail {

// creates matrix with initialized first layer
matrix_t initial_matrix(size_t rows, size_t cols) {
	matrix_t matrix(rows, row_t(cols));
	for (size_t j = 1; j < cols; ++j)
		matrix[0][j] = j;
	for (size_t i = 1; i < rows; ++i)
		matrix[i][0] = i;
	return matrix;
}

void set_current_min_distance(matrix_t& matrix, size_t i, size_t j, size_t cost) {
	matrix[i][j] = std::min({
		matrix[i][j - 1] + 1,
		matrix[i - 1][j] + 1,
		matrix[i - 1][j - 1] + cost
	});
}

template <typename RowT>
void print_row(char th, const RowT& row) {
	constexpr size_t column_width = 6;
	std::cout << std::setw(column_width) << th;
	for (auto&& element: row)
		std::cout << std::setw(column_width) << element;
	std::cout << '\n';
}

void print_matrix(const std::string& src, const std::string& dst, const matrix_t& matrix) {
	print_row(' ', " " + dst);
	print_row(' ', matrix[0]);
	for (size_t i = 1; i != matrix.size(); ++i)
		print_row(src[i - 1], matrix[i]);
}

}  // namespace detail

}  // namespace levenshtein
