#ifndef LAB06_ALGS_EXHAUSTIVE_SEARCH_HPP_
#define LAB06_ALGS_EXHAUSTIVE_SEARCH_HPP_

#include <vector>
#include "graph/graph.hpp"

using Path = std::vector<size_t>;

double path_len(const Graph &graph, const Path &path);
std::pair<Path, double> exhaustive_search(const Graph &graph);

#endif  // LAB06_ALGS_EXHAUSTIVE_SEARCH_HPP_
