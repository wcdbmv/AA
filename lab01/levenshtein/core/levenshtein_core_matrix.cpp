#include "levenshtein_core.hpp"

#include "levenshtein_core_detail_matrix.hpp"

namespace levenshtein::core {

matrix_t matrix(const std::string& src, const std::string& dst) {
	auto matrix = matrix_with_initialized_first_layer(src.size() + 1, dst.size() + 1);

	if (src.empty() || dst.empty()) {
		return matrix;
	}

	for (size_t i = 1; i <= src.size(); ++i) {
		for (size_t j = 1; j <= dst.size(); ++j) {
			set_current_min_distance(matrix, i, j, src[i - 1] != dst[j - 1]);
		}
	}

	return matrix;
}

}  // namespace levenshtein::core
