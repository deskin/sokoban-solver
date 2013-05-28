#include "errors.h"
#include "level.h"

namespace sokoban {

level::positions_type::iterator
level::tile::pit() const
{
	throw tile_invalid_exception();
}

level::positions_type::iterator
level::tile::set_pit(level::positions_type::iterator i)
{
	throw tile_invalid_exception();
}

void
level::tile::unset_pit()
{
	throw tile_invalid_exception();
}

} // namespace sokoban
