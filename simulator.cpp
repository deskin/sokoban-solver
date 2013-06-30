#include <string>
#include <vector>

#include "analyze.h"
#include "errors.h"
#include "level.h"
#include "level_mover.h"
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

bool
prune(const sokoban::simulator::steps_type &levels)
{
	const sokoban::level &level = levels.back();
	for (size_t i = levels.size() - 1; i / 2 > 0;) {
		i -= 2;
		if (level == levels[i]) {
			return true;
		}
	}

	return false;
}

} // namespace detail

namespace sokoban {

namespace det = ::detail;

simulator::simulator(const std::string &s) :
	level_steps(1),
	solve_call_count(0),
	has_run(false)
{
	level_steps[0].parse(s);
}

det::solve_status
simulator::solve(size_t max_steps)
{
	++solve_call_count;

	if (level_steps.size() > max_steps) {
		return det::solve_status::too_deep;
	}

	if (det::prune(level_steps)) {
		return det::solve_status::pruned;
	}

	const level &current = level_steps.back();

	if (is_win(current)) {
		return det::solve_status::win;
	}

	det::solve_status children_status = det::solve_status::pruned;

	level_steps.push_back(level());
	for (const auto &l: level_mover(level_steps[level_steps.size() - 2])) {
		level_steps.back() = l;
		det::solve_status child_status = solve(max_steps);

		if (child_status == det::solve_status::win) {
			return det::solve_status::win;
		} else if (child_status == det::solve_status::too_deep) {
			children_status = child_status;
		}
	}

	level_steps.pop_back();

	return children_status;
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

	size_t max_steps = det::count_level_arrangements(level_steps[0]);
	size_t current_steps = 1;
	det::solve_status solved;

	do {
		solved = solve(current_steps);
		++current_steps;
	} while (solved == det::solve_status::too_deep &&
		current_steps <= max_steps);
}

} // namespace sokoban
