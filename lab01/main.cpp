#include <iostream>
#include <functional>
#include "levenshtein/levenshtein.hpp"

int usage() {
	std::cout << "Usage: levenshtein [-v|--verbose] <mode> <src> <dst>\n"
	          << "\tmode: matrix | damerau_matrix | damerau_recursive\n";
	return -1;
}

std::tuple<bool, std::function<levenshtein::func_type>, std::string, std::string, bool>
parse_args(int argc, char* argv[]) {
	if (argc != 4 && argc != 5) {
		return {false, 0, "", "", false};
	}

	bool verbose = false;
	bool ok = true;

	const bool delta = argc == 5;
	if (delta) {
		const std::string flag = argv[1];
		if (flag == "-v" || flag == "--verbose") {
			verbose = true;
		} else {
			ok = false;
		}
	}

	std::function<levenshtein::func_type> levenshtein_f;
	const std::string mode = argv[delta + 1];
	if (mode == "matrix") {
		levenshtein_f = levenshtein::matrix;
	} else if (mode == "damerau_matrix") {
		levenshtein_f = levenshtein::damerau_matrix;
	} else if (mode == "damerau_recursive") {
		levenshtein_f = levenshtein::damerau_recursive;
	} else {
		ok = false;
	}

	const std::string src = argv[delta + 2];
	const std::string dst = argv[delta + 3];

	return {verbose, levenshtein_f, src, dst, ok};
}

int main(int argc, char* argv[]) {
	const auto [verbose, levenshtein_f, src, dst, ok] = parse_args(argc, argv);
	if (!ok) {
		return usage();
	}

	const auto distance = levenshtein_f(src, dst, verbose);
	std::cout << (verbose ? "Levenshtein distance: " : "") << distance << '\n';
}
