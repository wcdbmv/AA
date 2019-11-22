#include "levenshtein_core.hpp"

#include <algorithm>
#include "levenshtein_core_detail_matrix.hpp"

namespace levenshtein::core {
inline namespace detail {

matrix_t matrix_with_initialized_first_layer(size_t rows, size_t cols) {
	matrix_t matrix(rows, row_t(cols));
	for (size_t j = 1; j < matrix[0].size(); ++j) {
		matrix[0][j] = j;
	}
	for (size_t i = 1; i < matrix.size(); ++i) {
		matrix[i][0] = i;
	}
	return matrix;
}

void initialize_second_layer(matrix_t& matrix, const std::string& src, const std::string& dst) {
	for (size_t j = 1; j <= dst.size(); ++j) {
		set_current_min_distance(matrix, 1, j, src[0] != dst[j - 1]);
	}
	for (size_t i = 1; i <= src.size(); ++i) {
		set_current_min_distance(matrix, i, 1, src[i - 1] != dst[0]);
	}
}

matrix_t initial_matrix(size_t rows, size_t cols) {
	matrix_t matrix(rows, row_t(cols));

	return matrix;
}

void set_current_min_distance(matrix_t& matrix, size_t i, size_t j, size_t cost) {
	matrix[i][j] = std::min({
		matrix[i][j - 1] + 1,
		matrix[i - 1][j] + 1,
		matrix[i - 1][j - 1] + cost
	});
}

}  // namespace detail
}  // namespace levenshtein::core
