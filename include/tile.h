#ifndef SOKOBAN_TILE_H_
#define SOKOBAN_TILE_H_

#include "errors.h"
#include "level.h"

namespace sokoban {

class tile {
public:
	enum class kind {
		invalid,
		valid
	};

	explicit tile(kind) {}

	level::positions_type::iterator pit() const
	{
		throw tile_invalid_exception();
	}

	level::positions_type::iterator
	set_pit(level::positions_type::iterator i)
	{
		throw tile_invalid_exception();
	}
};

} // namespace sokoban

#endif // SOKOBAN_TILE_H_
