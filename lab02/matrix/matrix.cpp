#include "matrix.hpp"

matrix_t create_matrix(size_t rows, size_t cols) {
	return matrix_t(rows, row_t(cols, 0));
}

matrix_t product(const matrix_t& m1, const matrix_t& m2) {
	const size_t l = m1.size();
	const size_t m = m2.size();

	if (!l || !m || m1[0].size() != m) {
		throw std::exception();
	}

	const size_t n = m2[0].size();

	auto result = create_matrix(l, n);
	for (size_t i = 0; i != l; ++i) {
		for (size_t j = 0; j != n; ++j) {
			for (size_t k = 0; k != m; ++k) {
				result[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return result;
}

namespace bad {
inline namespace detail {

row_t negative_row_products(const matrix_t& matrix, size_t rows, size_t cols) {
	auto result = row_t(rows, 0);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols / 2; j++) {
			result[i] = result[i] + matrix[i][2*j] * matrix[i][2*j + 1];
		}
	}

	return result;
}

row_t negative_col_products(const matrix_t& matrix, size_t rows, size_t cols) {
	auto result = row_t(rows, 0);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols / 2; j = j + 2) {
			result[i] = result[i] + matrix[2*j][i] * matrix[2*j + 1][i];
		}
	}

	return result;
}

}  // namespace detail

matrix_t coppersmith_winograd_product(const matrix_t& m1, const matrix_t& m2) {
	const size_t l = m1.size();
	const size_t m = m2.size();

	if (!l || !m || m1[0].size() != m) {
		throw std::exception();
	}

	const size_t n = m2[0].size();

	const auto mh = negative_row_products(m1, l, m);
	const auto mv = negative_col_products(m2, n, m);

	auto result = create_matrix(l, n);
	for (size_t i = 0; i < l; i++) {
		for (size_t j = 0; j < m; j++) {
			result[i][j] = -(mh[i] + mv[j]);
			for (size_t k = 0; k < n / 2; k++) {
				result[i][j] = result[i][j] + (m1[i][2*k + 1] + m2[2*k][j]) * (m1[i][2*k] + m2[2*k + 1][j]);
			}
		}
	}

	if (n % 2) {
		for (size_t i = 0; i < l; i++) {
			for (size_t j = 0; j < m; j++) {
				result[i][j] = result[i][j] + m1[i][n - 1] * m2[n - 1][j];
			}
		}
	}

	return result;
}

}  // namespace bad

namespace good {
inline namespace detail {

row_t negative_row_products(const matrix_t& matrix, size_t rows, size_t cols) {
	auto result = row_t(rows, 0);
	for (size_t i = 0; i != rows; ++i) {
		for (size_t j = 0; j < cols - 1; j += 2) {
			result[i] -= matrix[i][j] * matrix[i][j + 1];
		}
	}

	return result;
}

row_t negative_col_products(const matrix_t& matrix, size_t rows, size_t cols) {
	auto result = row_t(rows, 0.);
	for (size_t j = 0; j < cols - 1; j += 2) {
		for (size_t i = 0; i != rows; ++i) {
			result[i] -= matrix[j][i] * matrix[j + 1][i];
		}
	}

	return result;
}

}  // namespace detail

matrix_t coppersmith_winograd_product(const matrix_t& m1, const matrix_t& m2) {
	const size_t l = m1.size();
	const size_t m = m2.size();

	if (!l || !m || m1[0].size() != m) {
		throw std::exception();
	}

	const size_t n = m2[0].size();

	const auto mh = negative_row_products(m1, l, m);
	const auto mv = negative_col_products(m2, n, m);

	auto result = create_matrix(l, n);
	for (size_t i = 0; i != l; ++i) {
		for (size_t j = 0; j != m; ++j) {
			result[i][j] = mh[i] + mv[j];
			for (size_t k = 0; k < n - 1; k += 2) {
				result[i][j] += (m1[i][k + 1] + m2[k][j]) * (m1[i][k] + m2[k + 1][j]);
			}
		}
	}

	if (n & 1) {
		for (size_t i = 0; i != l; ++i) {
			for (size_t j = 0; j != m; ++j) {
				result[i][j] += m1[i][n - 1] * m2[n - 1][j];
			}
		}
	}

	return result;
}

}  // namespace good
