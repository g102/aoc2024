#include "common.h"
#include "imports.h"

inline long file_sum(auto start, auto len, auto val) {
	return val * (start * len + (len - 1) * len / 2);
}

ulong disk_sum_pt1(std::ranges::range auto disk) {
	ulong out = 0;
	size_t head = 0;
	size_t tail = disk.size() - 1;
	size_t head_sector = 0;

	while (true) {
		if (head % 2 == 0) {
			out += file_sum(head_sector, disk[head], head / 2);
			head_sector += disk[head];

			head++;
			if (head > tail)
				break;
		} else {
			while (disk[tail] == 0)
				tail -= 2;
			if (head > tail)
				break;

			if (disk[head] >= disk[tail]) {
				out += file_sum(head_sector, disk[tail], tail / 2);
				head_sector += disk[tail];
				disk[head] -= disk[tail];
				disk[tail] -= disk[tail];
			} else {
				out += file_sum(head_sector, disk[head], tail / 2);
				head_sector += disk[head];
				disk[tail] -= disk[head];
				disk[head] -= disk[head];
			}

			if (disk[head] == 0)
				head++;
		}
	}
	return out;
}

ulong disk_sum_pt2(std::ranges::range auto disk) {
	// cumulative index
	decltype(disk) sector(disk.size(), 0);
	for (size_t i = 1; i < sector.size(); i++)
		sector[i] = sector[i - 1] + disk[i - 1];

	// views for convenience
	auto files = disk | std::views::stride(2);
	auto spaces = disk | std::views::drop(1) | std::views::stride(2);
	auto files_sect = sector | std::views::stride(2);
	auto spaces_sect = sector | std::views::drop(1) | std::views::stride(2);

	// move files to the right where possible
	ulong out = 0;
	for (size_t it = files.size() - 1; it > 0; it--) {
		// find the first place where the file can go
		auto& filesize = files[it];
		auto cond = [filesize](auto x) { return x >= filesize; };
		auto dest_it = std::ranges::find_if(spaces, cond);
		size_t dest = dest_it - spaces.begin();

		// file can't be moved if there's no big enough space, or if it is
		// further to the right
		if (dest_it == spaces.end() || dest > it) {
			// if the file can't be moved, compute the checksum here and now
			out += file_sum(files_sect[it], filesize, it);
		} else {
			// if it can, compute checksum based on where it should move
			out += file_sum(spaces_sect[dest], filesize, it);

			// and shrink the available space accordingly
			spaces[dest] -= filesize;
			spaces_sect[dest] += filesize;
		}
	}

	return out;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	ulong part1 = 0, part2 = 0;

	std::string text = readfile(input);
	std::erase(text, '\n');
	input.close();

	std::vector<ushort> disk(text.size(), 0);
	std::ranges::transform(text, disk.begin(), [](char c) { return c - '0'; });
	if (disk.size() % 2 == 0)
		disk.pop_back();

	part1 = disk_sum_pt1(disk);
	part2 = disk_sum_pt2(disk);

	std::print("{}, {}\n", part1, part2);
}
