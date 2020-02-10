#include "colony.hpp"

#include <algorithm>

Colony::Colony(Graph &graph)
		: graph_(graph), pheromone_graph_(graph.size(), START_PHEROMONE) {}

std::pair<std::vector<size_t>, double> Colony::antAlgorithm(size_t start_vert) {
	std::vector<size_t> taboo_list = {start_vert};

	auto current_vertex = start_vert;
	while (taboo_list.size() != graph_.size()) {
		current_vertex = chose_vert(current_vertex, taboo_list);
		taboo_list.push_back(current_vertex);
	}

	double len = 0;
	for (size_t i = 0; i < taboo_list.size(); ++i) {
		if (i < taboo_list.size() - 1) {
			len += graph_.get(taboo_list.at(i), taboo_list.at(i + 1));
		}
		else {
			len += graph_.get(taboo_list.at(i), taboo_list.at(0));
		}
	}

	return std::make_pair(taboo_list, len);
}

void Colony::update_pheromone(const std::vector<std::vector<size_t>> &paths) {
	for (size_t i = 0; i < graph_.size(); ++i) {
		for (size_t j = 0; j < graph_.size(); ++j) {
			if (i == j) {
				continue;
			}

			pheromone_graph_.set(i, j, pheromone_graph_.get(i, j) * (1 - parameters_.p));
			if (pheromone_graph_.get(i, j) <= 1e-5) {
				pheromone_graph_.set(i, j, 0.3);
			}
		}
	}

	for (auto &path: paths) {
		for (size_t i = 0; i < path.size(); ++i) {
			size_t from = 0, to = 0;
			if (i != path.size() - 1) {
				from = path.at(i);
				to = path.at(i + 1);
			}
			else {
				from = path.at(i);
				to = path.at(0);
			}

			auto delta = parameters_.q / graph_.get(from, to);
			auto new_val = pheromone_graph_.get(from, to) + delta;
			pheromone_graph_.set(from, to, new_val);
			pheromone_graph_.set(to, from, new_val);
		}
	}
}

double Colony::random_probability() {
	return distribution(generator);
}

size_t Colony::chose_vert(size_t vertex, const std::vector<size_t> &taboo_list) {
	auto probability = random_probability();
	auto available_vertexes = graph_.get_available_vertices(vertex, taboo_list);

	auto probabilities = vertexes_probabilities(vertex, available_vertexes);
	auto denominator = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);

	double curr_prob = 0.0;
	for (auto &v: available_vertexes) {
		curr_prob += probabilities.at(v) / denominator;
		if (probability <= curr_prob) {
			return v;
		}
	}

	return available_vertexes[available_vertexes.size() - 1];
}

std::vector<double> Colony::vertexes_probabilities(size_t curr_vertex, const std::vector<size_t> &available_vertexes) {
	std::vector<double> probabilities(graph_.size(), 0);

	for (auto &v: available_vertexes) {
		probabilities.at(v) = static_cast<double &&>(
			std::pow(pheromone_graph_.get(curr_vertex, v), parameters_.a)
				* std::pow(1. / graph_.get(curr_vertex, v), parameters_.b)
		);
	}

	return probabilities;
}

SimulationResult Colony::simulation(Parameters parameters, size_t days) {
	pheromone_graph_ = Graph(graph_.size(), START_PHEROMONE);
	std::vector<size_t> best_path;
	double best_path_len = -1;
	parameters_ = parameters;
	size_t days_to_find = 0;

	for (size_t i = 0; i < days; ++i) {
		std::vector<std::vector<size_t>> day_paths(graph_.size());
		for (size_t v = 0; v < graph_.size(); ++v) {
			auto result = antAlgorithm(v);
			day_paths.at(v) = result.first;

			if (std::abs(best_path_len + 1) < std::numeric_limits<double>::epsilon() || result.second < best_path_len) {
				best_path = result.first;
				best_path_len = result.second;
				days_to_find = i + 1;
			}
		}
		update_pheromone(day_paths);
	}

	return {best_path, days_to_find, best_path_len};
}
