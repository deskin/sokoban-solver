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

} // namespace

namespace sokoban {

std::tuple<bool, level::tile::pointer_type>
level::tile::pit() const
{
	throw_if_invalid(valid);

	return std::make_tuple<bool,
			       pointer_type>(
		!!pit_valid,
		pointer_type(pit_pointer));
}

level::tile::pointer_type
level::tile::set_pit(level::tile::pointer_type i)
{
	throw_if_invalid(valid);

	using std::swap;
	swap(pit_pointer, i);
	pit_valid = true;

	return pit_pointer;
}

void
level::tile::unset_pit()
{
	throw_if_invalid(valid);

	pit_valid = false;
}

std::tuple<bool, level::tile::pointer_type>
level::tile::rock() const
{
	throw_if_invalid(valid);

	return std::make_tuple<bool,
			       pointer_type>(
		!!rock_valid,
		pointer_type(rock_pointer));
}

level::tile::pointer_type
level::tile::set_rock(level::tile::pointer_type i)
{
	throw_if_invalid(valid);

	using std::swap;
	swap(rock_pointer, i);
	rock_valid = true;

	return rock_pointer;
}

void
level::tile::unset_rock()
{
	throw_if_invalid(valid);

	rock_valid = false;
}

} // namespace sokoban
