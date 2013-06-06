#include "level.h"
#include "move.h"

namespace sokoban {

bool
can_move(const level &l, direction::value d)
{
	const level::position_type &avatar(l.avatar());
	const level::tiles_type &tiles(l.tiles());
	size_t column = avatar.first;
	size_t row = avatar.second;

	if (direction::up() == d) {
		if (0 == row) {
			return false;
		}

		--row;
	} else if (direction::right() == d) {
		if (tiles[row].size() - 1 == column) {
			return false;
		}

		++column;
	} else if (direction::down() == d) {
		if (tiles.size() - 1 == row) {
			return false;
		}

		++row;
	} else if (direction::left() == d) {
		if (0 == column) {
			return false;
		}

		--column;
	}

	const level::tile &tile(tiles[row][column]);

	return tile.is_valid();
}

} // namespace sokoban
