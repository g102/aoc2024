#include "imports.h"

using vec = std::vector<uint>;

vec operator-(const vec& lhs, const vec& rhs) {
	vec out(lhs.size(), 0);
	for (size_t i = 0; i < lhs.size(); i++) out[i] = lhs[i] - rhs[i];
	return out;
}

vec operator*(const vec& lhs, const vec& rhs) {
	vec out(lhs.size(), 0);
	for (size_t i = 0; i < lhs.size(); i++) out[i] = lhs[i] * rhs[i];
	return out;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	vec col1, col2;

	for (uint i1, i2; input >> i1 >> i2;) {
		col1.push_back(i1);
		col2.push_back(i2);
	}
	input.close();
	std::ranges::sort(col1);
	std::ranges::sort(col2);

	// part 1
	vec diff(col1.size(), 0);
	for (size_t i = 0; i < col1.size(); i++)
		diff[i] = col2[i] > col1[i] ? col2[i] - col1[i] : col1[i] - col2[i];
	part1 = std::ranges::fold_left(diff, 0, std::plus<uint>());

	// part 2
	vec counts(col1.size(), 0);
	for (size_t i = 0; i < col1.size(); i++)
		counts[i] = std::ranges::count(col2, col1[i]);
	part2 = std::ranges::fold_left(col1 * counts, 0, std::plus<uint>());

	std::print("{}, {}\n", part1, part2);
}
