#include <gtest/gtest.h>
#include "matrix/matrix.hpp"

TEST(MatrixTest, FunctionalTest) {
	std::vector<std::tuple<matrix_t, matrix_t, matrix_t>> tests = {
		{
			{
				{1, 2, 3},
				{1, 2, 3},
				{1, 2, 3},
			}, {
				{1, 2, 3},
				{1, 2, 3},
				{1, 2, 3},
			}, {
				{6, 12, 18},
				{6, 12, 18},
				{6, 12, 18},
			},
		}, {
			{
				{1, 2},
				{1, 2},
			}, {
				{1, 2},
				{1, 2},
			}, {
				{3, 6},
				{3, 6},
			},
		}, {
			{
				{2},
			}, {
				{2},
			}, {
				{4},
			},
		}, {
			{
				{1, -2, 3},
				{1, 2, 3},
				{1, 2, 3},
			}, {
				{-1, 2, 3},
				{1, 2, 3},
				{1, 2, 3}
			}, {
				{0, 4, 6},
				{4, 12, 18},
				{4, 12, 18},
			},
		},
	};

	for (auto&& [m1, m2, expected]: tests) {
		std::vector<matrix_t> results = {
			coppersmith_winograd_product(m1, m2),
			coppersmith_winograd_product(m1, m2, 1),
			coppersmith_winograd_product(m1, m2, 2),
			coppersmith_winograd_product(m1, m2, 4),
			coppersmith_winograd_product(m1, m2, 8),
		};

		for (auto&& result: results) {
			ASSERT_EQ(result.size(), expected.size());
			for (size_t i = 0; i != expected.size(); ++i) {
				ASSERT_EQ(result[i].size(), expected[i].size());
				for (size_t j = 0; j != expected[i].size(); ++j) {
					ASSERT_DOUBLE_EQ(result[i][j], expected[i][j]);
				}
			}
		}
	}
}
