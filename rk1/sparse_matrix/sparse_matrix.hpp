#ifndef RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_
#define RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_

#include <vector>
#include <istream>
#include <ostream>

template <typename T>
class SparseMatrix {
public:
	SparseMatrix(size_t height, size_t width, size_t reserve = STD_RESERVE) noexcept;
	void clear() noexcept;
	void append(size_t row_index, size_t col_index, T element);
	void sort() noexcept;


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
	[[nodiscard]] size_t new_reserve() const noexcept;
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
size_t SparseMatrix<T>::new_reserve() const noexcept {
	const size_t expect = reserved_ + STD_RESERVE;
	const size_t minus = expect % STD_RESERVE;
	return expect - minus;
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
		resize(new_reserve());
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
SparseMatrix<T> operator+(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	return SparseMatrix<T>(0, 0, 0);
}

template <typename T>
SparseMatrix<T> operator*(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	return SparseMatrix<T>(0, 0, 0);
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
