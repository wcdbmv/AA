#ifndef LAB01_LEVENSHTEIN_LEVENSHTEIN_HPP_
#define LAB01_LEVENSHTEIN_LEVENSHTEIN_HPP_

#include <string>

namespace levenshtein {

using func_type = size_t(const std::string& src, const std::string& dst, bool verbose);

func_type matrix;
func_type recursive;
func_type damerau;

}  // namespace levenshtein

#endif  // LAB01_LEVENSHTEIN_LEVENSHTEIN_HPP_
