#ifndef LAB01_LEVENSHTEIN_LEVENSHTEIN_DETAIL_MATRIX_HPP_
#define LAB01_LEVENSHTEIN_LEVENSHTEIN_DETAIL_MATRIX_HPP_

#include "core/levenshtein_core.hpp"

namespace levenshtein {
inline namespace detail {

void print_matrix(const std::string& src, const std::string& dst, const core::matrix_t& matrix);

template <core::matrix_func_type MatrixF>
size_t matrix_wrap(const std::string& src, const std::string& dst, bool verbose) {
	const auto matrix = MatrixF(src, dst);

	if (verbose) {
		print_matrix(src, dst, matrix);
	}

	return matrix.back().back();
}

}  // inline namespace detail
}  // namespace levenshtein

#endif  //LAB01_LEVENSHTEIN_LEVENSHTEIN_DETAIL_MATRIX_HPP_
