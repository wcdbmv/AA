#include "levenshtein_core.hpp"

#include <algorithm>

namespace levenshtein::core {
inline namespace detail {

size_t damerau_recursive(const std::string& src, size_t i, const std::string& dst, size_t j) {
	if (!i || !j) return i + j;

	size_t dist = std::min({
		damerau_recursive(src, i - 1, dst, j) + 1,
		damerau_recursive(src, i, dst, j - 1) + 1,
		damerau_recursive(src, i - 1, dst, j - 1) + (src[i - 1] != dst[j - 1])
	});

	if (i >= 2 && j >= 2 && src[i - 2] == dst[j - 1] && src[i - 1] == dst[j - 2]) {
		dist = std::min(damerau_recursive(src, i - 2, dst, j - 2) + 1, dist);
	}

	return dist;
}

}  // namespace detail

size_t damerau_recursive(const std::string& src, const std::string& dst) {
	return damerau_recursive(src, src.size(), dst, dst.size());
}

}  // namespace levenshtein::core
