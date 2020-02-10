#include "search.hpp"

#include <map>
#include <vector>

int standard(const std::string& str, const std::string& sub) {
	const auto str_size = str.size();
	const auto sub_size = sub.size();

	if (str_size < sub_size) {
		return -1;
	}

	for (size_t i = 0; i <= str_size - sub_size; ++i) {
		for (size_t j = 0, tmp_i = i; j < sub_size; ++j, ++tmp_i) {
			if (sub[j] != str[tmp_i]) {
				break;
			}
			if (j == sub_size - 1) {
				return static_cast<int>(i);
			}
		}
	}

	return -1;
}

std::vector<size_t> get_shift(const std::string& str, size_t size) {
	std::vector<size_t> shift(size);

	for (size_t i = 1; i < size; ++i) {
		size_t j = shift[i - 1];
		while (j > 0 && str[i] != str[j]) {
			j = shift[j - 1];
		}
		if (str[i] == str[j]) {
			++j;
		}
		shift[i] = j;
	}

	return shift;
}

int kmp(const std::string& str, const std::string& sub) {
	const auto str_size = str.size();
	const auto sub_size = sub.size();

	if (str_size < sub_size) {
		return -1;
	}

	const auto shift = get_shift(sub, sub_size);

	for (size_t j = 0, i = 0; i < str_size; ++i) {
		while (j > 0 && str[i] != sub[j]) {
			j = shift[j - 1];
		}
		if (str[i] == sub[j]) {
			++j;
		}
		if (j == sub_size) {
			return static_cast<int>(i - j + 1);
		}
	}

	return -1;
}

std::map<char, size_t> get_shift(const std::string& sub) {
	constexpr size_t alphabet_size = 256;

	const auto sub_size = sub.size();
	std::map<char, size_t> shift;

	for (size_t symb = 0; symb < alphabet_size; ++symb) {
		shift[static_cast<char>(symb)] = sub_size;
	}

	for (size_t symb = 0; symb < sub_size - 1; ++symb) {
		shift[static_cast<char>(sub[symb])] = sub_size - symb - 1;
	}

	return shift;
}

int bm(const std::string& str, const std::string& sub) {
	const auto str_size = static_cast<int>(str.size());
	const auto sub_size = static_cast<int>(sub.size());

	if (str_size < sub_size) {
		return -1;
	}

	const auto shift = get_shift(sub);

	int start = static_cast<int>(sub_size) - 1;
	int k = start;
	for (
		auto i = start, j = start;
		j >= 0 && i < str_size;
		i += shift.at(str[i])
	) {
		for (
			j = start, k = i;
			j >= 0 && str[k] == sub[j];
			--k, --j
		);
	}

	return k >= str_size - sub_size ? -1 : static_cast<int>(k + 1);
}

