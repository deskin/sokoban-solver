#include "level.h"
#include "move.h"

namespace sokoban {

namespace {

template <typename Direction, typename CheckDirection>
bool
can_move(const level &l, Direction, CheckDirection &&direction_func)
{
	const level::position_type &avatar(l.avatar());
	const level::tiles_type &tiles(l.tiles());
	size_t column = avatar.first;
	size_t row = avatar.second;

	if (!std::forward<CheckDirection>(direction_func)(
		tiles,
		row,
		column)) {
		return false;
	}

	const level::tile &tile(tiles[row][column]);

	return tile.is_valid();
}
} // namespace

bool
can_move(const level &l, direction::up)
{
	return can_move(
		l,
		direction::up(),
		[](
			const level::tiles_type &,
			size_t &row,
			size_t) -> bool
		{
			if (0 == row) {
				return false;
			}

			--row;
			return true;
		});
}

bool
can_move(const level &l, direction::right)
{
	return can_move(
		l,
		direction::right(),
		[](
			const level::tiles_type &tiles,
			size_t row,
			size_t &column) -> bool
		{
			if (tiles[row].size() - 1 == column) {
				return false;
			}

			++column;
			return true;
		});
}

bool
can_move(const level &l, direction::down)
{
	return can_move(
		l,
		direction::down(),
		[](
			const level::tiles_type &tiles,
			size_t &row,
			size_t) -> bool
		{
			if (tiles.size() - 1 == row) {
				return false;
			}

			++row;
			return true;
		});
}

bool
can_move(const level &l, direction::left)
{
	return can_move(
		l,
		direction::left(),
		[](
			const level::tiles_type &,
			size_t,
			size_t &column) -> bool
		{
			if (0 == column) {
				return false;
			}

			--column;
			return true;
		});
}


} // namespace sokoban
