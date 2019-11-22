#ifndef LAB01_LEVENSHTEIN_CORE_LEVENSHTEIN_CORE_DETAIL_MATRIX_HPP_
#define LAB01_LEVENSHTEIN_CORE_LEVENSHTEIN_CORE_DETAIL_MATRIX_HPP_

#include "levenshtein_core.hpp"

namespace levenshtein::core {
inline namespace detail {

matrix_t matrix_with_initialized_first_layer(size_t rows, size_t cols);
void initialize_second_layer(matrix_t& matrix, const std::string& src, const std::string& dst);
void set_current_min_distance(matrix_t& matrix, size_t i, size_t j, size_t cost);

}  // namespace detail
}  // namespace levenshtein::core

#endif  //LAB01_LEVENSHTEIN_CORE_LEVENSHTEIN_CORE_DETAIL_MATRIX_HPP_
