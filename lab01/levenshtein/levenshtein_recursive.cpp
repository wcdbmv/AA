#include "levenshtein.hpp"

#include <algorithm>
#include <iostream>

namespace levenshtein {

size_t recursive(const std::string& src, size_t i, const std::string& dst, size_t j, bool verbose) {
	if (verbose) {
		std::cout << "recursive(src: \"" << src << "\", i: " << i << ", dst: \"" << dst << "\", j: " << j << ");\n";
	}

	if (!i) return j;
	if (!j) return i;

	const size_t cost = src[i - 1] != dst[j - 1];

	return std::min({
		recursive(src, i - 1, dst, j, verbose) + 1,
		recursive(src, i, dst, j - 1, verbose) + 1,
		recursive(src, i - 1, dst, j - 1, verbose) + cost
	});
}

size_t recursive(const std::string& src, const std::string& dst, bool verbose = false) {
	return recursive(src, src.size(), dst, dst.size(), verbose);
}

}  // namespace levenshtein
