#include "levenshtein.hpp"

#include "levenshtein_detail_matrix.hpp"

namespace levenshtein {

size_t matrix(const std::string& src, const std::string& dst, bool verbose) {
	return matrix_wrap<core::matrix>(src, dst, verbose);
}

}  // namespace levenshtein
