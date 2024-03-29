#include "tuple-hack.h"
#include <type_traits>
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

template <direction::value D, bool M>
bool
can_move(
	const level &l,
	size_t row,
	size_t column,
	std::integral_constant<direction::value, D>,
	std::integral_constant<bool, M>);

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

template <direction::value D>
bool
check_rock(
	const level &l,
	size_t row,
	size_t column,
	std::integral_constant<direction::value, D>,
	move_type::avatar)
{
	typedef std::integral_constant<direction::value, D> Direction;
	return can_move(l, row, column, Direction(), move_type::rock());
}

template <direction::value D>
bool
check_rock(
	const level &,
	size_t,
	size_t,
	std::integral_constant<direction::value, D>,
	move_type::rock)
{
	return false;
}

template <direction::value D, bool M>
bool
can_move(
	const level &l,
	size_t row,
	size_t column,
	std::integral_constant<direction::value, D>,
	std::integral_constant<bool, M>)
{
	typedef std::integral_constant<direction::value, D> Direction;
	typedef std::integral_constant<bool, M> MoveType;
	if (!check_position(l.tiles(), row, column, Direction())) {
		return false;
	}

	const bool tile_valid(l.tiles()[row][column]);

	if (!tile_valid) {
		return false;
	} else if (l.rocks().end() !=
		l.rocks().find(std::make_pair(column, row))) {
		return check_rock(
			l,
			row,
			column,
			Direction(),
			MoveType());
	}

	return true;
}

template <direction::value D>
bool
can_move_(const level &l, std::integral_constant<direction::value, D>)
{
	typedef std::integral_constant<direction::value, D> Direction;
	const level::position_type &avatar(l.avatar());

	return can_move(
		l,
		avatar.second,
		avatar.first,
		Direction(),
		move_type::avatar());
}

template <direction::value D>
level
move_(const level &l, std::integral_constant<direction::value, D>)
{
	typedef std::integral_constant<direction::value, D> Direction;
	level::position_type avatar(l.avatar());
	level::position_type new_avatar(avatar);

	if (!can_move(
		l,
		avatar.second,
		avatar.first,
		Direction(),
		move_type::avatar())) {
		throw cannot_move_exception();
	}

	level new_level(l);
	const level::tiles_type &tiles(new_level.tiles());

	check_position(
		tiles,
		new_avatar.second,
		new_avatar.first,
		Direction());

	if (new_level.rocks().end() != new_level.rocks().find(new_avatar)) {
		level::position_type new_rock(new_avatar);

		check_position(
			tiles,
			new_rock.second,
			new_rock.first,
			Direction());

		new_level.move_rock(new_avatar, new_rock);
	}

	new_level.move_avatar(new_avatar);

	return new_level;
}

} // namespace

bool can_move(const level &l, direction::up)
{
	return can_move_(l, direction::up());
}

bool can_move(const level &l, direction::right)
{
	return can_move_(l, direction::right());
}

bool can_move(const level &l, direction::down)
{
	return can_move_(l, direction::down());
}

bool can_move(const level &l, direction::left)
{
	return can_move_(l, direction::left());
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
