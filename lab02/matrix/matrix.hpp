#ifndef LAB02_MATRIX_MATRIX_HPP_
#define LAB02_MATRIX_MATRIX_HPP_

#include <vector>

using row_t = std::vector<double>;
using matrix_t = std::vector<row_t>;

matrix_t create_matrix(size_t rows, size_t cols);

using product_func_type = matrix_t(const matrix_t&, const matrix_t&);

product_func_type product;

namespace bad {
product_func_type coppersmith_winograd_product;
}  // namespace bad

namespace good {
product_func_type coppersmith_winograd_product;
}  // namespace good

#endif  // LAB02_MATRIX_MATRIX_HPP_
