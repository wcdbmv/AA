#ifndef LAB01_LEVENSHTEIN_CORE_LEVENSHTEIN_CORE_HPP_
#define LAB01_LEVENSHTEIN_CORE_LEVENSHTEIN_CORE_HPP_

#include <string>
#include <vector>

namespace levenshtein::core {

using row_t = std::vector<size_t>;
using matrix_t = std::vector<row_t>;

using matrix_func_type = matrix_t(const std::string& src, const std::string& dst);
using recursive_func_type = size_t(const std::string& src, const std::string& dst);

matrix_func_type matrix;
matrix_func_type damerau_matrix;
recursive_func_type damerau_recursive;

}  // namespace levenshtein::core

#endif  // LAB01_LEVENSHTEIN_CORE_LEVENSHTEIN_CORE_HPP_
