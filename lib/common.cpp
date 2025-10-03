#include "common.h"

#include <regex>

std::string readfile(std::ifstream& in) {
	std::string out;
	in.seekg(0, std::ios::end);
	out.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(out.data(), out.length());
	in.seekg(0, std::ios::beg);
	return out;
}

std::tuple<std::string, size_t, size_t> readmap(std::ifstream& in) {
	std::string text = readfile(in);
	if (!text.ends_with('\n')) text.append(1, '\n');
	size_t rows = std::ranges::count(text, '\n');
	size_t cols = text.length() / rows - 1;
	std::erase(text, '\n');
	return {text, rows, cols};
}

std::vector<long> parseint(std::string_view src) {
	using sv_iter = std::regex_iterator<std::string_view::const_iterator>;
	std::vector<long> dest;
	std::regex rx(R"([+-]?\d+(?:\.\d+)?)");
	for (sv_iter it{src.begin(), src.end(), rx}; it != sv_iter{}; it++) 
		dest.push_back(std::stol((*it).str()));
	return dest;
}
