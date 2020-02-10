#include <iostream>
#include "string/search.hpp"

std::string input_string(const std::string& prompt) {
	std::string str;
	std::cout << "Enter " << prompt << ": ";
	std::cin >> str;
	return str;
}

int main() {
	const auto str = input_string("string");
	const auto sub = input_string("substring");

	std::cout << "Standard algorithm result: " << standard(str, sub) << std::endl;
	std::cout << "KMP algorithm result: " << kmp(str, sub) << std::endl;
	std::cout << "BM algorithm result: " << bm(str, sub) << std::endl;
}
