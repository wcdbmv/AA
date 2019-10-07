#include <vector>
#include <iomanip>
#include <iostream>
#include <functional>
#include "levenshtein/levenshtein.hpp"

uint64_t tick() {
	uint64_t d;

	__asm__ __volatile__ ("rdtsc" : "=A" (d));

	return d;
}

template <levenshtein::func_type LevenshteinF, size_t N>
uint64_t test_levenshtein(const std::string& src, const std::string& dst) {
	const uint64_t tb = tick();

	for (size_t i = 0; i != N; ++i) {
		LevenshteinF(src, dst, false);
	}

	const uint64_t te = tick();

	return (te - tb) / N;
}

int main() {
	std::vector<std::pair<std::string, std::string>> test_strings = {
		{"ab", "ba"},
		{"abc", "cba"},
		{"abcd", "dcba"},
		{"abcde", "edcba"},
		{"abcdef", "fedcba"},
		{"abcdefg", "gfedcba"},
		{"abcdefgh", "hgfedcba"},
		{"abcdefghi", "ihgfedcba"},
		{"abcdefghij", "jihgfedcba"},
	};

	std::vector<std::pair<std::string, std::function<uint64_t(const std::string&, const std::string&)>>> test_levenshtein_funcs = {
		{"matrix", test_levenshtein<levenshtein::matrix, 100>},
		{"recursive", test_levenshtein<levenshtein::recursive, 1>},
		{"damerau", test_levenshtein<levenshtein::damerau, 100>},
	};

	std::cout << "len";
	for (auto&& [title, test_func]: test_levenshtein_funcs) {
		std::cout << std::setw(15) << title;
	}
	std::cout << '\n';

	for (auto&& [src, dst]: test_strings) {
		std::cout << std::setw(3) << src.size();
		for (auto&& [title, test_func]: test_levenshtein_funcs) {
			std::cout << std::setw(15) << test_func(src, dst);
		}
		std::cout << '\n';
	}
}
