#include "matrix.hpp"
#include <functional>
#include <thread>

matrix_t create_matrix(size_t rows, size_t cols) {
	return matrix_t(rows, row_t(cols, 0));
}

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

inline namespace detail {

void parallelize(const std::function<void(size_t, size_t)>& function, size_t thread_count, size_t rows) {
	if (rows < thread_count) {
		thread_count = rows;
	}

	std::vector<std::thread> threads(thread_count);
	const size_t delta_i = rows / thread_count;
	size_t i_begin = 0;
	size_t i_end = delta_i;
	for (size_t i = 0; i + 1 < thread_count; ++i, i_begin = i_end, i_end += delta_i) {
		threads[i] = std::thread(function, i_begin, i_end);
	}

	threads.back() = std::thread(function, i_begin, rows);

	for (auto&& thread: threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

row_t negative_row_products(const matrix_t& matrix, size_t rows, size_t cols, size_t thread_count) {
	auto result = row_t(rows, 0);
	auto lambda = [&](size_t i_begin, size_t i_end) {
		for (size_t i = i_begin; i < i_end; ++i) {
			for (size_t j = 0; j < cols - 1; j += 2) {
				result[i] -= matrix[i][j] * matrix[i][j + 1];
			}
		}
	};

	parallelize(lambda, thread_count, rows);
	return result;
}

row_t negative_col_products(const matrix_t& matrix, size_t rows, size_t cols, size_t thread_count) {
	auto result = row_t(rows, 0.);
	auto lambda = [&](size_t i_begin, size_t i_end) {
		for (size_t i = i_begin; i < i_end; i++) {
			for (size_t j = 0; j < cols - 1; j += 2) {
				result[i] -= matrix[j][i] * matrix[j + 1][i];
			}
		}
	};

	parallelize(lambda, thread_count, rows);
	return result;
}

}  // namespace detail

matrix_t coppersmith_winograd_product(const matrix_t& m1, const matrix_t& m2, size_t thread_count) {
	const size_t l = m1.size();
	const size_t m = m2.size();

	if (!l || !m || m1[0].size() != m) {
		throw std::exception();
	}

	const size_t n = m2[0].size();

	row_t mh, mv;
	if (thread_count > 2) {
		std::thread mh_thread([&]() { mh = negative_row_products(m1, l, m); });
		std::thread mv_thread([&]() { mv = negative_col_products(m2, n, m); });
		mh_thread.join();
		mv_thread.join();
	} else {
		mh = negative_row_products(m1, l, m);
		mv = negative_col_products(m2, n, m);
	}

	auto result = create_matrix(l, n);
	auto lambda = [&](size_t i_begin, size_t i_end) {
		for (size_t i = i_begin; i < i_end; ++i) {
			for (size_t j = 0; j < m; ++j) {
				result[i][j] = mh[i] + mv[j];
				for (size_t k = 0; k < n - 1; k += 2) {
					result[i][j] += (m1[i][k + 1] + m2[k][j]) * (m1[i][k] + m2[k + 1][j]);
				}
			}
		}
	};

	parallelize(lambda, thread_count, l);

	if (n & 1) {
		for (size_t i = 0; i != l; ++i) {
			for (size_t j = 0; j != m; ++j) {
				result[i][j] += m1[i][n - 1] * m2[n - 1][j];
			}
		}
	}

	return result;
}
