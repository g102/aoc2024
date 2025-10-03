#include "common.h"
#include "imports.h"

#include <cmath>

std::vector<long> parse_case(std::ifstream& in) {
	// parses a single case, or returns {} if at the end of file
	std::vector<long> testcase;
	std::string temp;

	for (size_t i = 0; i < 3; ++i) {
		if (!getline(in, temp)) return {};

		auto parsed = parseint(temp);
		testcase.insert(testcase.end(), parsed.begin(), parsed.end());
	}
	getline(in, temp);  // pass one empty line between entries
	return testcase;
}

long solve_case_pt1(std::ranges::range auto& tc) {
	// tc = {a_00, a_01, a_10, a_11, b_0, b_1}

	// solve the linear system
	double det = tc[0] * tc[3] - tc[1] * tc[2];
	double na = (tc[3] * tc[4] - tc[2] * tc[5]) / det;
	double nb = (tc[0] * tc[5] - tc[1] * tc[4]) / det;

	// check if the solution is integer
	long xp_comp = tc[0] * (long)na + tc[2] * (long)nb;
	long yp_comp = tc[1] * (long)na + tc[3] * (long)nb;

	if (tc[4] == xp_comp and tc[5] == yp_comp)
		return 3 * na + nb;
	else
		return 0;
}

long solve_case_pt2(std::ranges::range auto& tc) {
	static const long delta = 10000000000000;
	tc[4] += delta;
	tc[5] += delta;
	return solve_case_pt1(tc);
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	ulong part1 = 0, part2 = 0;

	while (true) {
		auto tc = parse_case(input);
		if (tc.empty()) break;

		part1 += solve_case_pt1(tc);
		part2 += solve_case_pt2(tc);
	}

	std::print("{}, {}\n", part1, part2);
}
