#include "common.h"
#include "grid.h"
#include "imports.h"

#define NDIRS 4

struct guard {
	grid& g;
	size_t pos, dir;
	std::set<size_t> set_hist, set_hist_dir;
	std::vector<size_t> vec_hist_dir;

	int solve_from(size_t _posdir) {
		return solve_from(_posdir / NDIRS, _posdir % NDIRS);
	}

	int solve_from(size_t _pos, size_t _dir) {
		// set-up
		pos = _pos;
		dir = _dir;

		set_hist.clear();
		set_hist_dir.clear();
		vec_hist_dir.clear();

		vec_hist_dir.push_back(pos * NDIRS + dir);

		// solve
		int retval = -1;
		while (true) {
			retval = advance();
			if (retval) return retval;
		}
	}

	int advance() {
		// advance the guard until she has either found a wall or has exited
		// return: 0 if still in maze, 1 if exited, 2 if in a loop

		while (true) {
			// check if the next move would put us out of bounds (exit the maze)
			static const std::array dr{-1, 0, 1, 0}, dc{0, 1, 0, -1};
			size_t ir = pos / g.cols, ic = pos % g.cols;
			size_t newrow = ir + dr[dir], newcol = ic + dc[dir];
			if (newrow >= g.rows || newcol >= g.cols) return 1;

			// from here on out, the next move for sure is in the maze -> safe
			// to use single index instead of (ix_row, ix_col)
			size_t newpos = newrow * g.cols + newcol;
			size_t newposdir = newpos * NDIRS + dir;

			if (set_hist_dir.contains(newposdir)) return 2;

			if (g[newpos] != '#') {
				pos = newpos;
				set_hist.insert(newpos);
				set_hist_dir.insert(newposdir);
				vec_hist_dir.push_back(newposdir);
			} else {
				dir = (dir + 1) % NDIRS;
				return 0;
			}
		}
	}
};

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	uint part1 = 0, part2 = 0;

	auto [text, rows, cols] = readmap(input);
	input.close();

	grid g{text, rows, cols};
	guard p{g};

	// part 1: simple solve from the specified starting point
	auto initial_pos = text.find('^');
	p.solve_from(initial_pos, 0);
	part1 = p.set_hist.size();

	// part 2: for each tile that the guard occupies, put a block, then count
	// how many result in a loop
	auto seq_pt1 = p.vec_hist_dir;
	std::set<size_t> done;
	for (size_t ix = 0; ix < seq_pt1.size() - 1; ix++) {
		auto pos_block = seq_pt1[ix + 1] / NDIRS;
		if (pos_block == initial_pos) continue;
		if (done.contains(pos_block)) continue;

		char old = g[pos_block];
		g[pos_block] = '#';
		if (p.solve_from(seq_pt1[ix]) == 2) part2++;
		g[pos_block] = old;
		done.insert(pos_block);
	}

	std::print("{}, {}\n", part1, part2);
}
