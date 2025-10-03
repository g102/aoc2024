#include "common.h"
#include "imports.h"

#include <cmath>

using rec = std::map<long, long>;

std::vector<long> next(long x) {
	if (x == 0) return {1};

	long ndigits = std::floor(std::log10(x)) + 1;
	if (ndigits % 2 == 0) {
		int splitter = pow(10, ndigits / 2);
		return {x / splitter, x % splitter};
	}

	return {x * 2024};
}

rec blink(rec& old_rec) {
	rec new_rec;
	for (auto& old_stone: old_rec | std::views::keys) {
		for (auto& new_stone: next(old_stone)) {
			if (new_rec.contains(new_stone))
				new_rec[new_stone] += old_rec[old_stone];
			else
				new_rec.insert({new_stone, old_rec[old_stone]});
		}
	}
	return new_rec;
}

ulong count_stones(rec& stones) {
	return std::ranges::fold_left(std::views::values(stones), 0, std::plus());
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");

	std::string temp;
	getline(input, temp);
	input.close();

	rec stones;
	for (auto& stone : parseint(temp)) stones.insert({stone, 1});

	for (size_t i = 0; i < 75; ++i) {
		stones = blink(stones);
		if (i == 24) std::print("{}, ", count_stones(stones));
		if (i == 74) std::print("{}\n", count_stones(stones));
	}
}
