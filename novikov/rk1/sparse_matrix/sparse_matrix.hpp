#ifndef RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_
#define RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_

#include <functional>
#include <fstream>
#include <istream>
#include <ostream>
#include <thread>
#include <vector>
#include <experimental/iterator>

template <typename T>
class SparseMatrix {
public:
	SparseMatrix();
	SparseMatrix(size_t height, size_t width, size_t size);
	SparseMatrix(const SparseMatrix& other);
	SparseMatrix(SparseMatrix&& other) noexcept;
	SparseMatrix& operator=(const SparseMatrix& other);
	SparseMatrix& operator=(SparseMatrix&& other) noexcept;

	static SparseMatrix read(const std::string& filename);

	template <typename T_>
	friend std::istream& operator>>(std::istream& os, SparseMatrix<T_>& sm);

	template <typename T_>
	friend std::ostream& operator<<(std::ostream& os, const SparseMatrix<T_>& sm);

	template <typename T_>
	friend SparseMatrix<T_> operator+(const SparseMatrix<T_>& lhs, const SparseMatrix<T_>& rhs);

private:
	size_t height_;
	size_t width_;
	size_t size_;

	std::vector<size_t> row_pointers_;
	std::vector<size_t> col_indices_;
	std::vector<T> elements_;
};

template <typename T>
SparseMatrix<T>::SparseMatrix() :
	height_(0),
	width_(0),
	size_(0),
	row_pointers_(1),
	col_indices_(0),
	elements_(0) { }

template <typename T>
SparseMatrix<T>::SparseMatrix(size_t height, size_t width, size_t size) :
	height_(height),
	width_(width),
	size_(size),
	row_pointers_(height + 1),
	col_indices_(size),
	elements_(size) { }

template <typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix& other) :
	height_(other.height_),
	width_(other.width_),
	size_(other.size_),
	row_pointers_(other.row_pointers_),
	col_indices_(other.col_indices_),
	elements_(other.elements_) { }

template <typename T>
SparseMatrix<T>::SparseMatrix(SparseMatrix&& other) noexcept :
	height_(other.height_),
	width_(other.width_),
	size_(other.size_),
	row_pointers_(std::move(other.row_pointers_)),
	col_indices_(std::move(other.col_indices_)),
	elements_(std::move(other.elements_)) { }

template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix<T>& other) {
	if (this != other) {
		height_ = other.height_;
		width_ = other.width_;
		size_ = other.size_;
		row_pointers_ = other.row_pointers_;
		col_indices_ = other.col_indices_;
		elements_ = other.elements_;
	}
	return *this;
}

template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator=(SparseMatrix<T>&& other) noexcept {
	if (this != other) {
		height_ = other.height_;
		width_ = other.width_;
		size_ = other.size_;
		row_pointers_ = std::move(other.row_pointers_);
		col_indices_ = std::move(other.col_indices_);
		elements_ = std::move(other.elements_);
	}
	return *this;
}

template <typename T>
std::istream& operator>>(std::istream& is, SparseMatrix<T>& sm) {
	is >> sm.height_ >> sm.width_ >> sm.size_;

	sm.row_pointers_.resize(sm.height_ + 1);
	sm.col_indices_.resize(sm.size_);
	sm.elements_.resize(sm.size_);

	for (auto& row_pointer: sm.row_pointers_) {
		is >> row_pointer;
	}

	for (auto& col_index: sm.col_indices_) {
		is >> col_index;
	}

	for (auto& element: sm.elements_) {
		is >> element;
	}

	return is;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::read(const std::string& filename) {
	SparseMatrix sm;

	std::ifstream file;
	file.open(filename);
	file >> sm;
	file.close();

	return sm;
}

template <typename Container>
void print_container(std::ostream& os, const Container& container) {
	std::copy(container.begin(), container.end(), std::experimental::make_ostream_joiner(os, " "));
	os << '\n';
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SparseMatrix<T>& sm) {
	os << sm.height_ << ' ' << sm.width_ << ' ' << sm.size_ << '\n';
	print_container(os, sm.row_pointers_);
	print_container(os, sm.col_indices_);
	print_container(os, sm.elements_);
	return os;
}

void parallelize(const std::function<void(size_t, size_t)>& function, size_t thread_count, size_t rows) {
	thread_count = std::min(rows, thread_count);
	std::vector<std::thread> threads(thread_count);

	const size_t delta_i = rows / thread_count;
	size_t i_begin = 0;
	size_t i_end = delta_i;
	for (size_t i = 0; i + 1 < thread_count; ++i, i_begin = i_end, i_end += delta_i) {
		threads[i] = std::thread(function, i_begin, i_end);
	}

	threads.back() = std::thread(function, i_begin, rows);

	for (auto& thread: threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

template <typename T>
SparseMatrix<T> operator+(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
	if (lhs.height_ != rhs.height_ || lhs.width_ != rhs.width_) {
		throw std::invalid_argument("Two matrices must have an equal number of rows and columns to be added");
	}

	SparseMatrix<T> result(lhs.height_, lhs.width_, 0);
	for (size_t i = 0; i < lhs.height_; ++i) {
		std::vector<bool> ix(lhs.height_, false);
		result.row_pointers_[i] = result.size_;
		for (size_t jp = lhs.row_pointers_[i]; jp < lhs.row_pointers_[i + 1]; ++jp) {
			const size_t j = lhs.col_indices_[jp];
			result.col_indices_.push_back(j);
			++result.size_;
			ix[j] = true;
		}
		for (size_t jp = rhs.row_pointers_[i]; jp < rhs.row_pointers_[i + 1]; ++jp) {
			const size_t j = rhs.col_indices_[jp];
			if (!ix[j]) {
				result.col_indices_.push_back(j);
				++result.size_;
			}
		}
	}
	result.row_pointers_[result.height_] = result.size_;
	result.elements_.resize(result.size_);

	auto lambda = [&](size_t i_begin, size_t i_end) {
		std::vector<T> x(lhs.width_, 0);
		for (size_t i = i_begin; i < i_end; ++i) {
			for (size_t ip = result.row_pointers_[i]; ip < result.row_pointers_[i + 1]; ++ip) {
				x[result.col_indices_[ip]] = 0;
			}
			for (size_t ip = lhs.row_pointers_[i]; ip < lhs.row_pointers_[i + 1]; ++ip) {
				x[lhs.col_indices_[ip]] = lhs.elements_[ip];
			}
			for (size_t ip = rhs.row_pointers_[i]; ip < rhs.row_pointers_[i + 1]; ++ip) {
				x[rhs.col_indices_[ip]] += rhs.elements_[ip];
			}
			for (size_t ip = result.row_pointers_[i]; ip < result.row_pointers_[i + 1]; ++ip) {
				result.elements_[ip] = x[result.col_indices_[ip]];
			}
		}
	};

	parallelize(lambda, 4, lhs.height_);
	return result;
}

#endif  // RK1_SPARSE_MATRIX_SPARSE_MATRIX_HPP_
