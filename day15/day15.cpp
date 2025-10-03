#include "imports.h"

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test.txt");
	uint part1 = 0, part2 = 0;

	std::print("{}, {}\n", part1, part2);
}
