#ifndef AOC24_GRID_H
#define AOC24_GRID_H

#include "imports.h"
#include <exception>

struct grid {
	std::string& text;
	size_t &rows, &cols;

	size_t size() const;

	void print() const;

	/* indexing conversions */
	size_t sub2ix(size_t, size_t) const;
	std::array<size_t, 2> ix2sub(size_t) const;

	/* access via operator overload */
	char& operator[](size_t);
	char& operator()(size_t, size_t);

	char operator[](size_t) const;
	char operator()(size_t, size_t) const;

	/* iterators to data */
	std::string::iterator begin();
	std::string::iterator end();

	/* neighbours */
	std::vector<std::string::iterator> neigh(size_t) const;
	std::vector<std::string::iterator> neigh(size_t, size_t) const;
};

#endif
