#ifndef SORT_SORT_HPP_
#define SORT_SORT_HPP_

#include <functional>

template <typename Iterator, typename Compare = std::less<>>
using sort_func_type = void(Iterator, Iterator, Compare);

template <typename Iterator, typename Compare = std::less<>>
void bubble_sort(Iterator first, Iterator last, Compare compare = Compare()) {
	for (auto i = first; i < last; ++i) {
		for (auto j = first; j < i; ++j) {
			if (compare(*i, *j)) {
				std::iter_swap(i, j);
			}
		}
	}
}

template <typename Iterator, typename Compare = std::less<>>
void insertion_sort(Iterator first, Iterator last, Compare compare = Compare()) {
	for (auto i = first + 1; i < last; ++i) {
		for (auto j = i; j > first && compare(*j, *(j - 1)); --j) {
			std::iter_swap(j, j - 1);
		}
	}
}

template <typename Iterator, typename Compare = std::less<>>
void selection_sort(Iterator first, Iterator last, Compare compare = Compare()) {
	for (; first < last; ++first) {
		std::swap(*std::min_element(first, last, compare), *first);
	}
}

#endif  // SORT_SORT_HPP_
