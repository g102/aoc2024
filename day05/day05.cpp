#include "common.h"
#include "imports.h"

using map = std::map<int, std::set<int>>;
using vec = std::vector<long>;

int valid(const vec& update, map& deps) {
	using std::ranges::set_intersection;
	for (size_t i = 0; i < update.size(); i++) {
		vec out_of_order;
		auto& specific = deps[update[i]];
		auto post = to<std::set<int>>(update | std::views::drop(i + 1));
		set_intersection(post, specific, std::back_inserter(out_of_order));

		if (!out_of_order.empty())
			return 0;
	}
	return update[update.size() / 2];
}

int sort_to_valid(vec& update, map& deps) {
	using namespace std::ranges;
	auto index = [&update](int x) { return find(update, x) - update.begin(); };

	for (size_t i = 0; i < update.size(); i++) {
		vec out_of_order;
		auto& specific = deps[update[i]];
		auto post = to<std::set<int>>(update | std::views::drop(i + 1));
		set_intersection(post, specific, std::back_inserter(out_of_order));

		if (!out_of_order.empty()) {
			size_t ix_last = max(std::views::transform(out_of_order, index));
			update.insert(update.begin() + ix_last + 1, update[i]);
			update.erase(update.begin() + i);

			// as we moved the i-th item, a new item has taken its place
			// this item needs to be checked (as it could be out of order)
			i--;
		}
	}
	return update[update.size() / 2];
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	// graph of dependencies
	map deps;
	for (std::string temp; getline(input, temp);) {
		if (temp.empty())
			break;
		auto parsed = parseint(temp);

		if (!deps.contains(parsed[1]))
			deps.insert({parsed[1], {}});
		deps[parsed[1]].insert(parsed[0]);
	}

	// list of updates (each evaluated as it is read)
	for (std::string temp; getline(input, temp);) {
		auto update = parseint(temp);
		auto unsorted_score = valid(update, deps);
		part1 += unsorted_score;
		if (unsorted_score == 0)
			part2 += sort_to_valid(update, deps);
	}

	std::print("{}, {}\n", part1, part2);
}
