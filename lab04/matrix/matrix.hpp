#ifndef LAB02_MATRIX_MATRIX_HPP_
#define LAB02_MATRIX_MATRIX_HPP_

#include <vector>

using row_t = std::vector<double>;
using matrix_t = std::vector<row_t>;

matrix_t create_matrix(size_t rows, size_t cols);

using product_func_type = matrix_t(const matrix_t&, const matrix_t&);
using parallel_product_func_type = matrix_t(const matrix_t&, const matrix_t&, size_t);

product_func_type coppersmith_winograd_product;
parallel_product_func_type coppersmith_winograd_product;

#endif  // LAB02_MATRIX_MATRIX_HPP_
