#include <string>
#include <vector>

#include "analyze.h"
#include "errors.h"
#include "level.h"
#include "simulator.h"

namespace detail {

size_t
count_level_arrangements(const sokoban::level &l)
{
	size_t open_tiles = 0;
	for (const auto &row: l.tiles()) {
		for (const auto &tile: row) {
			if (tile.is_valid()) {
				++open_tiles;
			}
		}
	}

	size_t rock_count = l.rocks().size();
	size_t tile_product = open_tiles - rock_count;
	if (rock_count > tile_product) {
		rock_count = tile_product;
	}

	size_t rock_product = 1;

	for (; rock_count > 0; --open_tiles, --rock_count) {
		tile_product *= open_tiles;
		rock_product *= rock_count;
	}

	return tile_product / rock_product;
}

} // namespace detail

namespace sokoban {

simulator::simulator(const std::string &s) :
	level_steps(1),
	has_run(false)
{
	level_steps[0].parse(s);
}

bool
simulator::win() const
{
	if (!has_run) {
		throw simulator_not_run();
	}

	return is_win(level_steps.back());
}

void
simulator::run()
{
	has_run = true;

	size_t max_steps = detail::count_level_arrangements(level_steps[0]);
	if (max_steps) {}
}

} // namespace sokoban
