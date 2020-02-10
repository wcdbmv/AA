#include <random>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "sort/sort.hpp"

int dont_try_to_guess() {
	static thread_local std::mt19937 generator(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> distribution(-1000, 1000);
	return distribution(generator);
}

std::vector<int> generate_sorted_vector(size_t size) {
	std::vector<int> vector(size);
	int val = 0;
	for (auto&& it: vector) {
		it = val++;
	}
	return vector;
}

std::vector<int> generate_reverse_sorted_vector(size_t size) {
	std::vector<int> vector(size);
	int val = static_cast<int>(size);
	for (auto&& it: vector) {
		it = val--;
	}
	return vector;
}

std::vector<int> generate_random_vector(size_t size) {
	std::vector<int> vector(size);
	for (auto&& it: vector) {
		it = dont_try_to_guess();
	}
	return vector;
}

double count_time(sort_func_type<std::vector<int>::iterator> sort_func, const std::vector<int>& vector) {
	constexpr size_t N = 100;

	long long time = 0;
	for (int i = 0; i != N; ++i) {
		auto tmp = vector;

		const auto start = std::chrono::high_resolution_clock::now();
		sort_func(tmp.begin(), tmp.end(), std::less<>());
		const auto end = std::chrono::high_resolution_clock::now();

		time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	}

	return static_cast<double>(time) / 1.0e6 / N;
}

void test(size_t begin, size_t end, size_t step) {
	constexpr int column_width = 20;

	std::vector<std::tuple<std::function<std::vector<int>(size_t)>, std::string>> generators = {
		{generate_sorted_vector, "sorted"},
		{generate_reverse_sorted_vector, "reversed"},
		{generate_random_vector, "random"},
	};

	for (auto&& [generator, title]: generators) {
		std::cout
			<< '[' << title << "]\n"
			<< "size"
			<< std::setw(column_width) << "bubble"
			<< std::setw(column_width) << "insertion"
			<< std::setw(column_width) << "selection"
			<< '\n';

		for (size_t i = begin; i <= end; i += step) {
			const auto v = generator(i);
			std::cout
				<< std::setw(4) << i
				<< std::fixed
				<< std::setprecision(4)
				<< std::setw(column_width)
				<< count_time(bubble_sort, v)
				<< std::setw(column_width)
				<< count_time(insertion_sort, v)
				<< std::setw(column_width)
				<< count_time(selection_sort, v)
				<< '\n';
		}
		std::cout << '\n';
	}
}

int main() {
	test(100, 2000, 100);
}
