#ifndef LAB07_STRING_SEARCH_HPP_
#define LAB07_STRING_SEARCH_HPP_

#include <string>

int standard(const std::string& str, const std::string& sub);
int kmp(const std::string& str, const std::string& sub);
int bm(const std::string& str, const std::string& sub);

#endif  // LAB07_STRING_SEARCH_HPP_
