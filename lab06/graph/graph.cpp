#include "graph.hpp"

#include <algorithm>
#include <chrono>
#include <random>

Graph::Graph(size_t vertices_count, double init_value)
		: adjacency_matrix_(vertices_count, std::vector<double>(vertices_count, init_value)) {}

void Graph::add_path(size_t vertex_from, size_t vertex_to, int length) {
	adjacency_matrix_.at(vertex_from).at(vertex_to) = length;
}

std::vector<size_t> Graph::get_available_vertices(size_t vertex, const std::vector<size_t> &taboo_list) const {
	std::vector<size_t > result;
	for (size_t i = 0; i < adjacency_matrix_.size(); ++i) {
		if (adjacency_matrix_.at(vertex).at(i) > 0 and std::find(taboo_list.begin(), taboo_list.end(), i) == taboo_list.end()) {
			result.push_back(i);
		}
	}
	return result;
}

void Graph::set(size_t i, size_t j, double value) {
	adjacency_matrix_.at(i).at(j) = value;
}

double Graph::get(size_t i, size_t j) const {
	return adjacency_matrix_.at(i).at(j);
}

size_t Graph::size() const {
	return adjacency_matrix_.size();
}

Graph Graph::generate_graph(size_t size, int noise) {
	std::default_random_engine generator(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> distribution(1, noise);

	Graph graph(size);
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			graph.set(i, j, distribution(generator));
		}
	}

	return graph;
}
