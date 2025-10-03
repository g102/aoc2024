#include "common.h"
#include "imports.h"

bool is_hash(char c) { return c == '#'; }

uint32_t string_to_uint(std::string line) {
	// note: all blocks are 5 columns and 7 rows -> 35 bits, but
	// the first row is always all # or all . -> crop to the last 32 chars
	// and save it as a uint32
	uint32_t outval = 0;
	std::erase(line, '\n');
	auto tail = line | std::views::reverse | std::views::take(32) |
	            std::views::reverse | std::views::transform(is_hash);
	for (size_t i = 0; i < tail.size(); i++) outval = outval | (tail[i] << i);
	return outval;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "test.txt");
	std::string text = readfile(input);
	text.append(1, '\n');  // so that the file ends with a double new-line
	std::vector<uint32_t> keys, locks;

	size_t it = 0, it_old = 0;
	while (true) {
		// load all blocks of text
		it = text.find("\n\n", it_old);
		if (it == text.npos) break;
		uint32_t temp = string_to_uint(text.substr(it_old, it - it_old));

		if (temp & 1 << 31)
			locks.push_back(temp);
		else
			keys.push_back(temp);
		it_old = it + 2;
	}

	uint part1 = 0;
	for (size_t il = 0; il < locks.size(); il++) {
		const auto& lock = locks[il];
		for (size_t ik = 0; ik < keys.size(); ik++) {
			const auto& key = keys[ik];
			if ((key & lock) == 0) part1++;
		}
	}
	std::print("{}, \n", part1);
}
