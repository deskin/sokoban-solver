#define SOKOBAN_CAN_MOVE_DEFINED
#include <utility>

#include "errors.h"
#include "level.h"
#include "move.h"

namespace sokoban {

namespace {

namespace move_type {

typedef std::true_type avatar;
typedef std::false_type rock;

} // namespace move_type

template <typename Direction, typename MoveType>
bool
can_move(
	const level::tiles_type &tiles,
	size_t row,
	size_t column,
	Direction,
	MoveType);

bool
check_position(
	const level::tiles_type &,
	size_t &row,
	size_t,
	direction::up)
{
	if (0 == row) {
		return false;
	}

	--row;
	return true;
}

bool
check_position(
	const level::tiles_type &tiles,
	size_t row,
	size_t &column,
	direction::right)
{
	if (tiles[row].size() - 1 == column) {
		return false;
	}

	++column;
	return true;
}

bool
check_position(
	const level::tiles_type &tiles,
	size_t &row,
	size_t,
	direction::down)
{
	if (tiles.size() - 1 == row) {
		return false;
	}

	++row;
	return true;
}

bool
check_position(
	const level::tiles_type &,
	size_t,
	size_t &column,
	direction::left)
{
	if (0 == column) {
		return false;
	}

	--column;
	return true;
}

template <typename Direction>
bool
check_rock(
	const level::tiles_type &tiles,
	size_t row,
	size_t column,
	Direction,
	move_type::avatar)
{
	return can_move(tiles, row, column, Direction(), move_type::rock());
}

template <typename Direction>
bool
check_rock(
	const level::tiles_type &,
	size_t,
	size_t,
	Direction,
	move_type::rock)
{
	return false;
}

template <typename Direction, typename MoveType>
bool
can_move(
	const level::tiles_type &tiles,
	size_t row,
	size_t column,
	Direction,
	MoveType)
{
	if (!check_position(tiles, row, column, Direction())) {
		return false;
	}

	const level::tile &tile(tiles[row][column]);

	if (!tile.is_valid()) {
		return false;
	} else if (std::get<0>(tile.rock())) {
		return check_rock(
			tiles,
			row,
			column,
			Direction(),
			MoveType());
	}

	return true;
}

template <typename Direction>
level
move_(const level &l, Direction)
{
	level::position_type avatar(l.avatar());
	level::position_type new_avatar(avatar);

	if (!can_move(
		l.tiles(),
		avatar.second,
		avatar.first,
		Direction(),
		move_type::avatar())) {
		throw cannot_move_exception();
	}

	level::positions_type pits(l.pits());
	level::positions_type rocks(l.rocks());
	level::tiles_type tiles(l.tiles());

	check_position(tiles, new_avatar.second, new_avatar.first, Direction());
	tiles[avatar.second][avatar.first].unset_avatar();
	tiles[new_avatar.second][new_avatar.first].set_avatar();

	return level(
		new_avatar.second,
		new_avatar.first,
		std::move(pits),
		std::move(rocks),
		std::move(tiles));
}

} // namespace

template <typename Direction>
bool
can_move(const level &l, Direction)
{
	const level::position_type &avatar(l.avatar());

	return can_move(
		l.tiles(),
		avatar.second,
		avatar.first,
		Direction(),
		move_type::avatar());
}

level
move(const level &l, direction::up)
{
	return move_(l, direction::up());
}

level move(const level &l, direction::right)
{
	return move_(l, direction::right());
}

level move(const level &l, direction::down)
{
	return move_(l, direction::down());
}

level move(const level &l, direction::left)
{
	return move_(l, direction::left());
}


} // namespace sokoban
