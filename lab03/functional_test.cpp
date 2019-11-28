#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include <vector>
#include "sort/sort.hpp"

TEST(SortTest, FunctionalTest) {
	std::vector<std::vector<int>> vs = {
		{1, 2, 3, 4, 5},
		{5, 4, 3, 2, 1, 0},
		{5, 6, 2, 1, 4, -2},
		{4},
		{},
	};

	for (auto&& v: vs) {
		auto bv = v, iv = v, sv = v;
		auto expected = v;
		bubble_sort(bv.begin(), bv.end());
		insertion_sort(iv.begin(), iv.end());
		selection_sort(sv.begin(), sv.end());
		std::sort(expected.begin(), expected.end());
		ASSERT_EQ(bv, expected);
		ASSERT_EQ(iv, expected);
		ASSERT_EQ(sv, expected);
	}
}
