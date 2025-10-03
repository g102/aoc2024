#include "common.h"
#include "grid.h"
#include "imports.h"

struct patch {
	grid& g;
	std::set<size_t> tiles;

	patch(grid& _g, size_t start) : g(_g) { populate(start); }

	void populate(size_t ix) {
		if (tiles.contains(ix)) return;

		tiles.insert(ix);
		for (auto& n : g.neigh(ix)) {
			if (*n != g[ix]) continue;
			populate(n - g.begin());
		}
	}

	std::vector<bool> all_around(size_t ix) {
		std::vector<bool> out;
		auto add_if = [&](size_t x) {
			out.push_back(tiles.contains(x) && g[ix] == g[x]);
		};

		std::array circle{ix + 1,          ix + 1 - g.cols, ix - g.cols,
		                  ix - g.cols - 1, ix - 1,          ix - 1 + g.cols,
		                  ix + g.cols,     ix + g.cols + 1, ix + 1};
		for (auto& c : circle) add_if(c);

		return out;
	}

	uint perimeter() {
		uint peri = 0;
		for (size_t t : tiles) {
			peri += 4;
			for (auto& n : g.neigh(t)) {
				if (tiles.contains(n - g.begin())) --peri;
			}
		}
		return peri;
	}


	uint corners() {
		uint cor = 0;
		for (size_t t : tiles) {
			auto test = all_around(t);
			for (size_t iq = 0; iq < 4; ++iq) {
				auto qd = std::views::drop(test, iq * 2) | std::views::take(3);
				if (!qd[0] && !qd[2]) ++cor;
				if (qd[0] && !qd[1] && qd[2]) ++cor;
			}
		}
		return cor;
	}

	uint score_pt1() { return tiles.size() * perimeter(); }
	uint score_pt2() { return tiles.size() * corners(); }
};

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	auto [text, rows, cols] = readmap(input);
	input.close();

	grid g{text, rows, cols};

	std::set<size_t> seen;
	for (size_t ix = 0; ix < text.size(); ix++) {
		if (seen.contains(ix)) continue;

		patch temp(g, ix);
		part1 += temp.score_pt1();
		part2 += temp.score_pt2();

		for (auto& t : temp.tiles) seen.insert(t);
	}

	std::print("{}, {}\n", part1, part2);
}
