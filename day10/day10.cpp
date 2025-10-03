#include "common.h"
#include "grid.h"
#include "imports.h"

void get_trail_score(grid& g, size_t ix, std::set<size_t>& s, uint& counter) {
	if (g[ix] == '9') {
		s.insert(ix);
		++counter;
	}

	for (auto& n : g.neigh(ix))
		if (*n == g[ix] + 1)
			get_trail_score(g, n - g.begin(), s, counter);
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	auto [text, rows, cols] = readmap(input);
	input.close();

	grid g{text, rows, cols};

	for (size_t ix = 0;; ++ix) {
		ix = text.find('0', ix);
		if (ix == text.npos)
			break;

		std::set<size_t> s;
		get_trail_score(g, ix, s, part2);
		part1 += s.size();
	}

	std::print("{}, {}\n", part1, part2);
}
