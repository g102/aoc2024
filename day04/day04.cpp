#include "common.h"
#include "imports.h"

#define LEN 4
#define SQR 3

struct Text {
	std::string_view text;
	size_t &rows, cols;
};

auto helper(Text& t, size_t ix, size_t s) {
	using namespace std::views;
	return t.text | drop(ix) | stride(s) | take(LEN);
}

auto row(Text& t, size_t ix) {
	return helper(t, ix, 1);
}
auto col(Text& t, size_t ix) {
	return helper(t, ix, t.cols);
}
auto dgp(Text& t, size_t ix) {
	return helper(t, ix, t.cols + 1);
}
auto dgn(Text& t, size_t ix) {
	return helper(t, ix, t.cols - 1);
}

auto xsh(Text& t, size_t ix) {
	using coord = std::array<size_t, 2>;
	std::array<coord, 5> coords{{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}};

	std::string out(coords.size(), ' ');
	for (size_t i = 0; i < coords.size(); i++)
		out[i] = t.text[ix + t.cols * coords[i][0] + coords[i][1]];
	return out;
}

bool checker_pt1(std::ranges::view auto x) {
	std::string t(x.begin(), x.end());
	return t == "XMAS" || t == "SAMX";
}

bool checker_pt2(const std::string& x) {
	return x == "MSAMS" || x == "MMASS" || x == "SSAMM" || x == "SMASM";
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	auto [text, rows, cols] = readmap(input);
	input.close();

	Text t(text, rows, cols);

	for (size_t i = 0; i < text.length(); i++) {
		size_t ir = i / cols, ic = i % cols;
		if (ir + LEN - 1 < rows)
			part1 += checker_pt1(col(t, i));
		if (ic + LEN - 1 < cols)
			part1 += checker_pt1(row(t, i));
		if (ir + LEN - 1 < rows && ic + LEN - 1 < cols)
			part1 += checker_pt1(dgp(t, i));
		if (ir + LEN - 1 < rows && ic >= LEN - 1)
			part1 += checker_pt1(dgn(t, i));
		if (ir + SQR - 1 < rows && ic + SQR - 1 < cols)
			part2 += checker_pt2(xsh(t, i));
	}

	std::print("{}, {}\n", part1, part2);
}
