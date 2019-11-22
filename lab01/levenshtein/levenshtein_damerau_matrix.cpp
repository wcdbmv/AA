#include "levenshtein.hpp"

#include "levenshtein_detail_matrix.hpp"

namespace levenshtein {

size_t damerau_matrix(const std::string& src, const std::string& dst, bool verbose) {
	return matrix_wrap<core::damerau_matrix>(src, dst, verbose);
}

}  // namespace levenshtein
