#include "grid.h"

void grid::print() const {
	for (size_t ir = 0; ir < rows; ir++)
		std::print("{}\n", text.substr(cols * ir, cols));
}

size_t grid::size() const {
	return rows * cols;
}

/* indexing conversions */
size_t grid::sub2ix(size_t i0, size_t i1) const {
	return i0 * cols + i1;
}
std::array<size_t, 2> grid::ix2sub(size_t ix) const {
	return {ix / cols, ix % cols};
}

/* accessing via operator overload */
char& grid::operator[](size_t ix) {
	return text[ix];
}
char& grid::operator()(size_t i0, size_t i1) {
	return text[sub2ix(i0, i1)];
}

char grid::operator[](size_t ix) const {
	return text[ix];
}
char grid::operator()(size_t i0, size_t i1) const {
	return text[sub2ix(i0, i1)];
}

/* iterators to data */
std::string::iterator grid::begin() {
	return text.begin();
}
std::string::iterator grid::end() {
	return text.end();
}

/* neighbours */
std::vector<std::string::iterator> grid::neigh(size_t ix) const {
	std::vector<std::string::iterator> out;
	auto [ir, ic] = ix2sub(ix);

	if (ir > 0) out.push_back(text.begin() + ix - cols);         // up
	if (ic < cols - 1) out.push_back(text.begin() + ix + 1);     // right
	if (ir < rows - 1) out.push_back(text.begin() + ix + cols);  // down
	if (ic > 0) out.push_back(text.begin() + ix - 1);            // left
	return out;
}

std::vector<std::string::iterator> grid::neigh(size_t i0, size_t i1) const {
	return neigh(sub2ix(i0, i1));
}
