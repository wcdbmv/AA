#include "exhaustive_search.hpp"

#include <algorithm>
#include <queue>
#include <numeric>

double path_len(const Graph &graph, const Path &path) {
	double len = 0;
	for (size_t i = 0; i < path.size() - 1; ++i) {
		len += graph.get(path[i], path[i+1]);
	}
	len += graph.get(path[path.size()-1], path[0]);
	return len;
}

std::pair<Path, double> exhaustive_search(const Graph &graph) {
	Path best_path(graph.size());
	double best_path_len = -1;
	std::vector<size_t> empty_v;
	std::queue<std::vector<size_t>> queue;
	queue.push(std::vector<size_t>(1, 0));

	while (!queue.empty()) {
		std::vector<size_t> u = queue.front();
		queue.pop();
		for (auto v: graph.get_available_vertices(u[u.size()-1], empty_v)) {
			if (std::find(u.begin(), u.end(), v) == u.end()) {
				std::vector<size_t> new_path(u.size());
				std::copy(u.begin(), u.end(), new_path.begin());
				new_path.push_back(v);
				if (new_path.size() == graph.size()) {
					auto len = path_len(graph, new_path);
					if (len < best_path_len || std::abs(best_path_len + 1) < std::numeric_limits<double>::epsilon()) {
						best_path_len = len;
						best_path = new_path;
					}
				} else {
					queue.push(new_path);
				}
			}
		}
	}

	return std::make_pair(best_path, best_path_len);
}
