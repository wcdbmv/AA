#include "levenshtein.hpp"

#include "core/levenshtein_core.hpp"

namespace levenshtein {

size_t damerau_recursive(const std::string& src, const std::string& dst, bool) {
	return core::damerau_recursive(src, dst);
}

}  // namespace levenshtein
