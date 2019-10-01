#include "levenshtein.hpp"

#include "detail.hpp"

namespace levenshtein {

size_t matrix(const std::string& src, const std::string& dst, bool verbose = false) {
	if (src.empty()) return dst.size();
	if (dst.empty()) return src.size();

	auto matrix = initial_matrix(src.size() + 1, dst.size() + 1);

	for (size_t i = 1; i <= src.size(); ++i)
		for (size_t j = 1; j <= dst.size(); ++j)
			set_current_min_distance(matrix, i, j, src[i - 1] != dst[j - 1]);

	if (verbose) {
		print_matrix(src, dst, matrix);
	}

	return matrix.back().back();
}

}  // namespace levenshtein
