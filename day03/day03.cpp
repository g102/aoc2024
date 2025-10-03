#include "common.h"
#include "imports.h"

#include <regex>

void remover(std::string& t) {
	size_t ix_begin = 0, ix_end = 0;

	while (true) {
		ix_begin = t.find("don't()", 0);
		ix_end = t.find("do()", ix_begin);
		if (ix_end == t.npos) break;
		t.erase(ix_begin, ix_end - ix_begin + 4);
	}	
}

int counter(std::string_view t) {
	using sv_iter = std::regex_iterator<std::string_view::const_iterator>;
	std::regex matcher("mul\\((\\d{1,3}),(\\d{1,3})\\)");

	int ctr = 0;
	for (sv_iter it(t.begin(), t.end(), matcher); it != sv_iter{}; it++)
		ctr += std::stoi((*it)[1]) * std::stoi((*it)[2]);
	return ctr;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	auto text = readfile(input);
	input.close();
	
	part1 = counter(text);
	remover(text);
	part2 = counter(text);

	std::print("{}, {}\n", part1, part2);
}
