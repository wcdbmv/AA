#include <cmath>
#include <iostream>
#include "algs/colony.hpp"
#include "algs/exhaustive_search.hpp"

Parameters get_best_params(Parameters &parameters, Graph &graph, double path_len) {
	static constexpr const auto A_B_CONST = 1.f;
	static constexpr const auto A_DELTA = .1f;
	auto eps = 1.f / path_len;
	Parameters best_params = {0, 0, 0, 0, 0, 0};
	size_t iterations = 401;

	Colony colony(graph);
	for (auto a = 0.f; a < A_B_CONST + A_DELTA; a += A_DELTA) {
		for (auto p = 0.f; p <= 1.f; p += 0.1f) {
			size_t times = 400;
			parameters.a = a;
			parameters.b = A_B_CONST - a;
			parameters.p = p;

			auto res = colony.simulation(parameters, times);

			std::cout << parameters.a << " " << parameters.b << " " << parameters.p << " "
				  << res.days << " " << res.path_len << std::endl;

			if (res.days < iterations && std::fabs(res.path_len - path_len) < eps) {
				iterations = static_cast<size_t>(res.days);
				best_params = parameters;
				best_params.times = static_cast<size_t>(std::ceil(res.days));
			}
		}
	}

	return best_params;
}

int main() {
	size_t cities_num = 10;

	auto graph = Graph::generate_graph(cities_num, 5);
	auto ex_res = exhaustive_search(graph);
	std::cout << ex_res.second << std::endl << std::endl;

	Parameters parameters{};
	parameters.q = ex_res.second / static_cast<double>(ex_res.first.size());
	auto result = get_best_params(parameters, graph, ex_res.second);

	std::cout << "a: " << result.a << std::endl;
	std::cout << "b: " << result.b << std::endl;
	std::cout << "p: " << result.p << std::endl;
	std::cout << "Iterations: " << result.times << std::endl;

	graph = Graph::generate_graph(cities_num, 15000);
	ex_res = exhaustive_search(graph);
	std::cout << ex_res.second << std::endl << std::endl;

	parameters.q = ex_res.second / static_cast<double>(ex_res.first.size());
	result = get_best_params(parameters, graph, ex_res.second);

	std::cout << "a: " << result.a << std::endl;
	std::cout << "b: " << result.b << std::endl;
	std::cout << "p: " << result.p << std::endl;
	std::cout << "Iterations: " << result.times << std::endl;

	return 0;
}
