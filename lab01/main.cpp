#include <iostream>
#include <functional>
#include "levenshtein/levenshtein.hpp"

int usage() {
	std::cout << "Usage: levenshtein [-v|--verbose] <mode> <src> <dst>\n"
	          << "\tmode: matrix | recursive | damerau\n";
	return -1;
}

bool check_argc(int argc) {
	return argc == 4 || argc == 5;
}

std::tuple<bool, std::function<levenshtein::func_type>, std::string, std::string, bool>
parse_args(int argc, char* argv[]) {
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
	} else if (mode == "recursive") {
		levenshtein_f = levenshtein::recursive;
	} else if (mode == "damerau") {
		levenshtein_f = levenshtein::damerau;
	} else {
		ok = false;
	}

	const std::string src = argv[delta + 2];
	const std::string dst = argv[delta + 3];

	return {verbose, levenshtein_f, src, dst, ok};
}

int main(int argc, char* argv[]) {
	if (!check_argc(argc)) {
		return usage();
	}

	const auto [verbose, levenshtein_f, src, dst, ok] = parse_args(argc, argv);
	if (!ok) {
		return usage();
	}

	const auto distance = levenshtein_f(src, dst, verbose);
	std::cout << (verbose ? "Levenshtein distance: " : "") << distance << '\n';
}
