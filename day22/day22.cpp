#include "imports.h"

long next(long curr) {
	curr = ((curr << 6) ^ curr) & 0xffffff;
	curr = ((curr >> 5) ^ curr) & 0xffffff;
	curr = ((curr << 11) ^ curr) & 0xffffff;
	return curr;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test.txt");
	long long part1 = 0;
	for (long secret; input >> secret;) {
		for (size_t i = 0; i < 2000; i++) {
			secret = next(secret);
		}
		part1 += secret;
	}
	std::print("{}\n", part1);
}
