#ifndef LAB01_LEVENSHTEIN_MATRIX_HPP_
#define LAB01_LEVENSHTEIN_MATRIX_HPP_

#include <vector>
#include <string>

namespace levenshtein {

inline namespace detail {

using row_t = std::vector<size_t>;
using matrix_t = std::vector<row_t>;

matrix_t initial_matrix(size_t rows, size_t cols);
void set_current_min_distance(matrix_t& matrix, size_t i, size_t j, size_t cost);

void print_matrix(const std::string& src, const std::string& dst, const matrix_t& matrix);

}  // namespace detail

}  // namespace levenshtein

#endif  // LAB01_LEVENSHTEIN_MATRIX_HPP_
