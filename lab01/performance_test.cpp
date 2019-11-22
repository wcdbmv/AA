#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include "levenshtein/core/levenshtein_core.hpp"

template <typename T>
T randint(T a, T b) {
	static thread_local std::mt19937 generator(std::random_device{}());
	static thread_local std::uniform_int_distribution<T> distribution(a, b);
	return distribution(generator);
}

std::string randstring(size_t length) {
	std::string string(length, 0);

	for (size_t i = 0; i != length; ++i) {
		string[i] = randint('a', 'z');
	}

	return string;
}

using InputT = std::vector<std::pair<std::string, std::string>>;

InputT tests_strings(size_t start, size_t step, size_t count) {
	InputT strings(count);

	for (size_t i = 0; i != count; ++i) {
		strings[i].first = randstring(start + i*step);
		strings[i].second = randstring(start + i*step);
	}

	return strings;
}

template <typename F, typename... Args>
double time(size_t N, F func, Args&&... args) {
	if (!N) {
		return 0;
	}

	const auto start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i != N; ++i) {
		func(std::forward<Args>(args)...);
	}

	const auto end = std::chrono::high_resolution_clock::now();

	return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1.0e6 / N;
}


void test(const InputT& strings, size_t nm, size_t ndm, size_t ndr) {
	for (auto&& [src, dst]: strings) {
		std::cout << std::setw(4) << src.size();
		std::cout << std::setw(20) << time(nm, levenshtein::core::matrix, src, dst)
		          << std::setw(20) << time(ndm, levenshtein::core::damerau_matrix, src, dst)
		          << std::setw(20) << time(ndr, levenshtein::core::damerau_recursive, src, dst)
		          << std::endl;
	}
}

int main() {
	auto soft_test_strings = tests_strings(2, 1, 9);
	auto medium_test_strings = tests_strings(20, 10, 8);
	auto hard_test_strings = tests_strings(100, 100, 10);

	std::cout << " len              matrix      damerau_matrix   damerau_recursive\n";
	test(soft_test_strings, 100, 100, 1);
	test(medium_test_strings, 100, 100, 0);
	test(hard_test_strings, 10, 10, 0);
}
