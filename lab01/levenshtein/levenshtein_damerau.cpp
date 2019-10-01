#include "levenshtein.hpp"

#include <algorithm>
#include "detail.hpp"

namespace levenshtein {

inline namespace detail {

void init_second_layer(matrix_t& matrix, const std::string& src, const std::string& dst) {
	for (size_t j = 1; j <= dst.size(); ++j)
		set_current_min_distance(matrix, 1, j, src[0] != dst[j - 1]);
	for (size_t i = 1; i <= src.size(); ++i)
		set_current_min_distance(matrix, i, 1, src[i - 1] != dst[0]);
}

}  // namespace detail

size_t damerau(const std::string& src, const std::string& dst, bool verbose = false) {
	if (src.empty()) return dst.size();
	if (dst.empty()) return src.size();

	auto matrix = initial_matrix(src.size() + 1, dst.size() + 1);
	init_second_layer(matrix, src, dst);

	for (size_t i = 2; i <= src.size(); ++i) {
		for (size_t j = 2; j <= dst.size(); ++j) {
			const size_t cost = src[i - 1] != dst[j - 1];
			set_current_min_distance(matrix, i, j, cost);

			if (src[i - 1] == dst[j - 2] && src[i - 2] == dst[j - 1]) {
				matrix[i][j] = std::min(matrix[i - 2][j - 2] + cost, matrix[i][j]);
			}
		}
	}

	if (verbose) {
		print_matrix(src, dst, matrix);
	}

	return matrix.back().back();
}

}  // namespace levenshtein
