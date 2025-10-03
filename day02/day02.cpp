#include "common.h"
#include "imports.h"

using vec = std::vector<long>;

bool safe(vec& v, bool part2 = false) {
	if (v.front() < v.back()) std::ranges::reverse(v);
	auto diff = std::views::pairwise_transform(v, std::minus<int>());

	for (size_t i = 0; i < diff.size(); i++) {
		if (diff[i] > 3 || diff[i] < 1) {
			if (part2) {
				auto v1 = v, v2 = v;
				v1.erase(v1.begin() + i);
				v2.erase(v2.begin() + i + 1);
				return (safe(v1) || safe(v2));
			} else
				return false;
		}
	}

	return true;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	for (std::string temp; getline(input, temp);) {
		vec x = parseint(temp);
		if (safe(x)) part1++;
		if (safe(x, true)) part2++;
	}
	input.close();

	std::print("{}, {}\n", part1, part2);
}
