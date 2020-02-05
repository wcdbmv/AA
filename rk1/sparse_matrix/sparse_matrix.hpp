#ifndef RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_
#define RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_

#include <vector>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>

template <typename T>
class SparseMatrix {
public:
	SparseMatrix(size_t height, size_t width, size_t reserve = STD_RESERVE) noexcept;
	void clear() noexcept;
	void append(size_t row_index, size_t col_index, T element);
	void sort() noexcept;
	void RRCU(std::ostream& os);

public:
	template <typename T_>
	friend SparseMatrix<T_> operator+(const SparseMatrix<T_>& lhs, const SparseMatrix<T_>& rhs);
	template <typename T_>
	friend SparseMatrix<T_> operator*(const SparseMatrix<T_>& lhs, const SparseMatrix<T_>& rhs);

	template <typename T_>
	friend std::istream& operator>>(std::istream& is, SparseMatrix<T_>& sm);
	template <typename T_>
	friend std::ostream& operator<<(std::ostream& os, const SparseMatrix<T_>& sm);

private:
	void resize(size_t height, size_t width, size_t reserve);
	void resize(size_t reserve);
	[[nodiscard]] static size_t calc_reserve(size_t size) noexcept;
	[[nodiscard]] bool exists(size_t row_index, size_t col_index) const noexcept;

private:
	size_t height_;
	size_t width_;
	size_t reserved_;
	size_t size_;

	std::vector<size_t> row_indices_;
	std::vector<size_t> col_indices_;
	std::vector<T> elements_;

private:
	constexpr static size_t STD_RESERVE = 128;
};


# include <experimental/iterator>

template <typename T>
SparseMatrix<T>::SparseMatrix(size_t height, size_t width, size_t reserve) noexcept :
		height_(height),
		width_(width),
		reserved_(reserve),
		size_(0),
		row_indices_(reserve),
		col_indices_(reserve),
		elements_(reserve) { }

template <typename T>
void SparseMatrix<T>::clear() noexcept {
	height_ = 0;
	width_ = 0;
	reserved_ = 0;
	size_ = 0;
	row_indices_.clear();
	col_indices_.clear();
	elements_.clear();
}

template <typename T>
void SparseMatrix<T>::resize(size_t height, size_t width, size_t reserve) {
	height_ = height;
	width_ = width;
	reserved_ = reserve;
	size_ = 0;

	row_indices_.resize(reserve);
	col_indices_.resize(reserve);
	elements_.resize(reserve);
}

template <typename T>
void SparseMatrix<T>::resize(size_t reserve) {
	reserved_ = reserve;
	size_ = std::min(size_, reserved_);

	row_indices_.resize(reserve);
	col_indices_.resize(reserve);
	elements_.resize(reserve);
}

template <typename T>
size_t SparseMatrix<T>::calc_reserve(size_t size) noexcept {
	return size + STD_RESERVE - size % STD_RESERVE;
}

template <typename T>
bool SparseMatrix<T>::exists(size_t row_index, size_t col_index) const noexcept {
	for (size_t i = 0; i < size_; ++i) {
		if (row_indices_[i] == row_index && col_indices_[i] == col_index) {
			return true;
		}
	}
	return false;
}

template <typename T>
void SparseMatrix<T>::append(size_t row_index, size_t col_index, T element) {
	if (row_index >= height_ || col_index >= width_ || element == T(0)) {
		throw std::invalid_argument("Invalid element");
	}

	if (exists(row_index, col_index)) {
		throw std::invalid_argument("Element exists");
	}

	if (size_ == reserved_) {
		resize(calc_reserve(reserved_ + STD_RESERVE));
	}

	row_indices_[size_] = row_index;
	col_indices_[size_] = col_index;
	elements_[size_] = element;
	++size_;
}

template <typename T>
void SparseMatrix<T>::sort() noexcept {
	for (size_t i = 0; i + 1 < size_; ++i) {
		size_t i_min = i;
		for (size_t j = i + 1; j < size_; ++j) {
			if (row_indices_[j] < row_indices_[i] || (row_indices_[j] == row_indices_[i] && col_indices_[j] < col_indices_[i])) {
				i_min = j;
			}
		}

		if (i_min != i) {
			std::swap(row_indices_[i], row_indices_[i_min]);
			std::swap(col_indices_[i], col_indices_[i_min]);
			std::swap(elements_[i], elements_[i_min]);
		}
	}
}

template <typename T>
void SparseMatrix<T>::RRCU(std::ostream& os) {
	// must be sorted
	std::vector<size_t> ia(height_ + 1, 0);

	for (size_t k = 0; k < height_; ++k) {
		int begin = -1;
		int end = -1;
		for (size_t i = 0; i < size_; ++i) {
			if (row_indices_[i] == k) {
				if (begin == -1) {
					begin = static_cast<int>(i);
				}
			} else if (row_indices_[i] > k) {
				end = static_cast<int>(i);
				break;
			}
		}
		end = end == -1 ? static_cast<int>(size_) : end;
		if (k == 0) {
			if (begin == -1) {
				ia[k] = 0;
				ia[k + 1] = 0;
			} else {
				ia[k] = static_cast<size_t>(begin);
				ia[k + 1] = static_cast<size_t>(end);
			}
		} else {
			ia[k + 1] = static_cast<size_t>(end);
		}
	}
	ia[height_] = size_;

	os << height_<< ' ' << width_ << ' ' << size_ << '\n';
	std::copy(ia.begin(), ia.end(), std::experimental::make_ostream_joiner(os, " "));
	os << '\n';
	std::copy(col_indices_.begin(), col_indices_.begin() + static_cast<long int>(size_), std::experimental::make_ostream_joiner(os, " "));
	os << '\n';
	std::copy(elements_.begin(), elements_.begin() + static_cast<long int>(size_), std::experimental::make_ostream_joiner(os, " "));
	os << '\n';
}

template <typename T>
SparseMatrix<T> operator+(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	return SparseMatrix<T>(0, 0, 0);
}


template <typename T>
SparseMatrix<T> operator*(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	if (lhs.width_ != rhs.height_) {
		throw std::invalid_argument("Invalid matrices' sizes");
	}

	SparseMatrix<T> result(lhs.height_, rhs.width_, SparseMatrix<T>::calc_reserve(std::max(lhs.size_, rhs.size_)));
	std::vector<bool> ix(lhs.height_, false);

	return result;
}

template <typename T>
std::istream& operator>>(std::istream& is, SparseMatrix<T>& sm) {
	size_t height, width, reserve;
	is >> height >> width >> reserve;
	sm.resize(height, width, reserve);

	for (size_t i = 0; i < reserve; ++i) {
		size_t row_index, col_index;
		T element;
		is >> row_index >> col_index >> element;
		sm.append(row_index, col_index, element);
	}

	return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SparseMatrix<T>& sm) {
	os << sm.height_ << ' ' << sm.width_ << ' ' << sm.size_ << '\n';
	for (size_t i = 0; i < sm.size_; ++i) {
		os << sm.row_indices_[i] << ' ' << sm.col_indices_[i] << ' ' << sm.elements_[i] << '\n';
	}

	return os;
}

#endif  // RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_
