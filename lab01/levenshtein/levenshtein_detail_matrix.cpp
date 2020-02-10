#include "levenshtein_detail_matrix.hpp"

#include <iomanip>
#include <iostream>

namespace levenshtein {
inline namespace detail {

template <typename RowT>
void print_row(char th, const RowT& row) {
	constexpr size_t column_width = 6;

	std::cout << std::setw(column_width) << th;
	for (auto&& element: row) {
		std::cout << std::setw(column_width) << element;
	}
	std::cout << '\n';
}

void print_matrix(const std::string& src, const std::string& dst, const core::matrix_t& matrix) {
	print_row(' ', " " + dst);
	print_row(' ', matrix[0]);
	for (size_t i = 1; i != matrix.size(); ++i) {
		print_row(src[i - 1], matrix[i]);
	}
}

}  // namespace detail
}  // namespace levenshtein
