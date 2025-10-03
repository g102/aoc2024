#include "common.h"
#include "imports.h"

bool check_concat(long lhs, long rhs) {
	return std::to_string(lhs).ends_with(std::to_string(rhs));
}

long invert_concat(long lhs, long rhs) {
	auto s_lhs = std::to_string(lhs);
	auto s_rhs = std::to_string(rhs);
	s_lhs.erase(s_lhs.length() - s_rhs.length());
	return s_lhs.length() ? std::stol(s_lhs) : 0;
}

template <typename T>
bool valid(T& vec, bool p2 = false) {
	if (vec.size() == 2)
		return vec[0] == vec[1];

	bool retval = false;
	if (p2 && check_concat(vec.front(), vec.back())) {
		T newvec(vec.begin(), vec.end() - 1);
		newvec.front() = invert_concat(vec.front(), vec.back());
		retval = retval | valid(newvec, p2);
	}
	if (vec.front() % vec.back() == 0) {
		T newvec(vec.begin(), vec.end() - 1);
		newvec.front() /= vec.back();
		retval = retval | valid(newvec, p2);
	}
	if (vec.front() >= vec.back()) {
		T newvec(vec.begin(), vec.end() - 1);
		newvec.front() -= vec.back();
		retval = retval | valid(newvec, p2);
	}
	return retval;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	ulong part1 = 0, part2 = 0;

	for (std::string temp; getline(input, temp);) {
		auto vec = parseint(temp);
		if (valid(vec))
			part1 += vec[0];
		if (valid(vec, true))
			part2 += vec[0];
	}

	std::print("{}, {}\n", part1, part2);
}
