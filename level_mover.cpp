#include <vector>

#include "level.h"
#include "level_mover.h"
#include "move.h"

namespace sokoban {

level_mover::level_mover(const level &l) :
	levels()
{
	levels.reserve(4);

	if (can_move(l, direction::up())) {
		levels.emplace_back(move(l, direction::up()));
	}

	if (can_move(l, direction::right())) {
		levels.emplace_back(move(l, direction::right()));
	}

	if (can_move(l, direction::down())) {
		levels.emplace_back(move(l, direction::down()));
	}

	if (can_move(l, direction::left())) {
		levels.emplace_back(move(l, direction::left()));
	}
}

}
