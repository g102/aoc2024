#include "common.h"
#include "grid.h"
#include "imports.h"

using arr = std::array<long, 2>;

struct ant {
	char freq;
	size_t pos;
};

arr operator-(arr& lhs, arr& rhs) {
	arr out;
	for (size_t i = 0; i < out.size(); i++)
		out[i] = lhs[i] - rhs[i];
	return out;
}

arr operator+(arr& lhs, arr& rhs) {
	arr out;
	for (size_t i = 0; i < out.size(); i++)
		out[i] = lhs[i] + rhs[i];
	return out;
}

bool valid(grid& g, arr& x) {
	return (x[0] >= 0 && x[1] >= 0 && x[0] < (long)g.rows &&
	        x[1] < (long)g.cols);
}

void add_if_valid(grid& g, arr x, std::set<size_t>& s) {
	if (valid(g, x))
		s.insert(x[0] * g.cols + x[1]);
}

void podes(grid& g, ant& A, ant& B, std::set<size_t>& s, bool p2 = false) {
	if (A.freq != B.freq)
		return;

	arr pt_A{(long)A.pos / (long)g.cols, (long)A.pos % (long)g.cols};
	arr pt_B{(long)B.pos / (long)g.cols, (long)B.pos % (long)g.cols};
	arr delta = pt_B - pt_A;

	add_if_valid(g, pt_B + delta, s);
	add_if_valid(g, pt_A - delta, s);

	if (delta[0] % 3 == 0 && delta[1] % 3 == 0) {
		arr dd{delta[0] / 3, delta[1] / 3};
		add_if_valid(g, pt_B - dd, s);
		add_if_valid(g, pt_A + dd, s);
	}

	if (!p2)
		return;

	for (auto prev = pt_B - delta; valid(g, prev); prev = prev - delta) {
		add_if_valid(g, prev, s);
	}
	for (auto prev = pt_A + delta; valid(g, prev); prev = prev + delta) {
		add_if_valid(g, prev, s);
	}

	return;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	auto [text, rows, cols] = readmap(input);
	grid g{text, rows, cols};
	input.close();

	std::vector<ant> found;
	for (size_t i = 0;; i++) {
		i = text.find_first_not_of('.', i);
		if (i == std::string::npos)
			break;
		found.push_back({g[i], i});
	}

	std::set<size_t> set_pt1, set_pt2;
	for (size_t i = 0; i < found.size(); i++) {
		for (size_t j = i + 1; j < found.size(); j++) {
			podes(g, found[i], found[j], set_pt1);
			podes(g, found[i], found[j], set_pt2, true);
		}
	}

	part1 = set_pt1.size();
	part2 = set_pt2.size();

	std::print("{}, {}\n", part1, part2);
}
