#ifndef LAB01_LEVENSHTEIN_LEVENSHTEIN_HPP_
#define LAB01_LEVENSHTEIN_LEVENSHTEIN_HPP_

#include <string>
#include <vector>

namespace levenshtein {

using func_type = size_t(const std::string& src, const std::string& dst, bool verbose);

func_type matrix;
func_type damerau_matrix;
func_type damerau_recursive;

}  // namespace levenshtein

#endif  // LAB01_LEVENSHTEIN_LEVENSHTEIN_HPP_
