#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include "levenshtein/core/levenshtein_core.hpp"

TEST(LevenshteinTest, Functional) {
	std::vector<std::tuple<std::string, std::string, size_t, size_t>> tests = {
		{"dessert", "desert", 1, 1},
		{"cook", "cooker", 2, 2},
		{"mother", "money", 3, 3},
		{"woman", "water", 4, 4},
		{"program", "friend", 6, 6},
		{"house", "girl", 5, 5},
		{"probelm", "problem", 2, 1},
		{"head", "ehda", 3, 2},
		{"bring", "brought", 4, 4},
		{"happy", "happy", 0, 0},
		{"minute", "moment", 5, 5},
		{"person", "eye", 5, 5},
		{"week", "weeks", 1, 1},
		{"member", "morning", 6, 6},
		{"death", "health", 2, 2},
		{"education", "question", 4, 4},
		{"room", "moor", 2, 2},
		{"car", "city", 3, 3},
		{"air", "area", 3, 3},
	};

	for (auto&& [src, dst, expected_levenshtein, expected_damerau_levenshtein]: tests) {
		ASSERT_EQ(levenshtein::core::matrix(src, dst).back().back(), expected_levenshtein);
		ASSERT_EQ(levenshtein::core::damerau_matrix(src, dst).back().back(), expected_damerau_levenshtein);
		ASSERT_EQ(levenshtein::core::damerau_recursive(src, dst), expected_damerau_levenshtein);
	}
}
