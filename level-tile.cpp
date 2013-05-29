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

std::tuple<bool, level::positions_type::iterator>
level::tile::pit() const
{
	throw_if_invalid(valid);

	return std::make_tuple<bool,
			       positions_type::iterator>(
		!!pit_valid,
		positions_type::iterator(pit_pointer));
}

level::positions_type::iterator
level::tile::set_pit(level::positions_type::iterator i)
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

} // namespace sokoban
