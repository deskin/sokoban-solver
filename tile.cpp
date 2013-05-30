#include "tuple-hack.h"
#include <utility>

#include "errors.h"
#include "level.h"

namespace {

void throw_if_invalid(bool valid)
{
	if (!valid) {
		throw sokoban::tile_invalid_exception();
	}
}

const sokoban::level::tile::pointer_tuple &
get_pointer_tuple(const sokoban::level::tile::pointer_tuple &p, bool valid)
{
	throw_if_invalid(valid);

	return p;
}

void
set_pointer_tuple(
	sokoban::level::tile::pointer_tuple &p,
	sokoban::level::tile::pointer_type &&i,
	bool valid)
{
	throw_if_invalid(valid);

	using std::swap;
	swap(std::get<1>(p), i);
	std::get<0>(p) = true;
}

void
unset_pointer_tuple(
	sokoban::level::tile::pointer_tuple &p,
	bool valid)
{
	throw_if_invalid(valid);

	std::get<0>(p) = false;
}

} // namespace

namespace sokoban {

const level::tile::pointer_tuple &
level::tile::pit() const
{
	return get_pointer_tuple(pit_pointer, valid);
}

void
level::tile::set_pit(level::tile::pointer_type i)
{
	set_pointer_tuple(pit_pointer, std::move(i), valid);
}

void
level::tile::unset_pit()
{
	unset_pointer_tuple(pit_pointer, valid);
}

const level::tile::pointer_tuple &
level::tile::rock() const
{
	return get_pointer_tuple(rock_pointer, valid);
}

void
level::tile::set_rock(level::tile::pointer_type i)
{
	set_pointer_tuple(rock_pointer, std::move(i), valid);
}

void
level::tile::unset_rock()
{
	unset_pointer_tuple(rock_pointer, valid);
}

} // namespace sokoban
