#include "common.h"
#include "imports.h"

// TODO: part2

inline long mod(long lhs, long rhs) {
	return ((lhs % rhs) + rhs) % rhs;
}

struct robot {
	std::array<long, 2> pos, vel;
	const std::vector<long>& shape;

	robot(std::vector<long> _init, const auto& _s) : shape(_s) {
		pos = {_init[0], _init[1]};
		vel = {_init[2], _init[3]};
	}

	void step(int n = 1) {
		for (size_t i = 0; i < 2; i++)
			pos[i] = mod(pos[i] + vel[i] * n, shape[i]);
	}

	size_t quadrant() {
		if (pos[0] == shape[0] / 2 or pos[1] == shape[1] / 2) return -1;

		size_t out = 0;
		out += pos[0] < shape[0] / 2 ? 0 : 1;
		out += pos[1] < shape[1] / 2 ? 0 : 2;
		return out;
	}
};

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	ulong part1 = 0, part2 = 0;

	std::string temp;
	getline(input, temp);
	auto shape = parseint(temp);
	uint period = std::ranges::fold_left(shape, 1, std::multiplies());

	std::vector<robot> robots;
	while (getline(input, temp)) {
		robots.push_back(robot(parseint(temp), shape));
	}

	std::array<size_t, 4> quadrants{0, 0, 0, 0};
	for (size_t t = 0; t < period; t++) {
		for (auto& r : robots) {
			r.step();
			if (t == 99) {
				auto q = r.quadrant();
				if (q != -1uz) ++quadrants[q];
			}
		}
	}
	part1 = std::ranges::fold_left(quadrants, 1, std::multiplies());

	std::print("{}, {}\n", part1, part2);
}
