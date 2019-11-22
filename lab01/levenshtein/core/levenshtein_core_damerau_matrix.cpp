#include "levenshtein_core.hpp"

#include "levenshtein_core_detail_matrix.hpp"

namespace levenshtein::core {

matrix_t damerau_matrix(const std::string& src, const std::string& dst) {
	auto matrix = matrix_with_initialized_first_layer(src.size() + 1, dst.size() + 1);

	if (src.empty() || dst.empty()) {
		return matrix;
	}

	initialize_second_layer(matrix, src, dst);

	for (size_t i = 2; i <= src.size(); ++i) {
		for (size_t j = 2; j <= dst.size(); ++j) {
			const size_t cost = src[i - 1] != dst[j - 1];
			set_current_min_distance(matrix, i, j, cost);

			if (src[i - 1] == dst[j - 2] && src[i - 2] == dst[j - 1]) {
				matrix[i][j] = std::min(matrix[i - 2][j - 2] + cost, matrix[i][j]);
			}
		}
	}

	return matrix;
}

}  // namespace levenshtein::core
