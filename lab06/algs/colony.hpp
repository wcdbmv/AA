#ifndef LAB06_ALGS_COLONY_HPP_
#define LAB06_ALGS_COLONY_HPP_

#include <random>
#include "graph/graph.hpp"

struct Parameters {
	double a;
	double b;
	double p;
	double q;
	double start_pheromone;
	size_t times;
};

struct SimulationResult {
	std::vector<size_t> path;
	size_t days;
	double path_len;
};

class Colony {
public:
	explicit Colony(Graph &graph);
	SimulationResult simulation(Parameters parameters, size_t days);
private:
	static constexpr const double START_PHEROMONE = 0.3f;

	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0, 1);

	Graph graph_;
	Graph pheromone_graph_;
	Parameters parameters_;

	std::pair<std::vector<size_t>, double> antAlgorithm(size_t start_vert);
	double random_probability();
	std::vector<double> vertexes_probabilities(size_t curr_vertex, const std::vector<size_t> &available_vertexes);
	size_t chose_vert(size_t vertex, const std::vector<size_t> &taboo_list);
	void update_pheromone(const std::vector<std::vector<size_t>> &paths);
};

#endif  // LAB06_ALGS_COLONY_HPP_
