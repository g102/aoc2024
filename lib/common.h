#ifndef AOC24_COMMON_H
#define AOC24_COMMON_H

#include "imports.h"

std::string readfile(std::ifstream&);
std::tuple<std::string, size_t, size_t> readmap(std::ifstream&);
std::vector<long> parseint(std::string_view);

/* template functions */
void print_array(std::ranges::range auto& x) {
	for (auto& i: x) std::print("{} ", i);
	std::print("\n");
}

#endif
