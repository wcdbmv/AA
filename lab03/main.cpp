#include <iomanip>
#include <iostream>
#include <experimental/iterator>
#include "sort/sort.hpp"

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vector) {
	for (auto&& it: vector) {
		is >> it;
	}

	return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector) {
	std::copy(vector.begin(), vector.end(), std::experimental::make_ostream_joiner(os, " "));
	return os;
}

int main() {
	size_t size;
	std::cout << "Size: ";
	std::cin >> size;

	std::vector<int> v(size);
	std::cout << "Array: ";
	std::cin >> v;

	auto vb = v;
	auto vs = v;
	auto vi = v;

	bubble_sort(vb.begin(), vb.end());
	selection_sort(vs.begin(), vs.end());
	insertion_sort(vi.begin(), vi.end());

	std::cout << "\nBubble sort   : " << vb << "\nSelection sort: " << vs << "\nInsertion sort: " << vi << '\n';
}
