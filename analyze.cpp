#include "tuple-hack.h"
#include <utility>

#include "analyze.h"
#include "level.h"

namespace sokoban {

bool
is_win(const level &l)
{
	const level::tiles_type &tiles(l.tiles());
	const level::positions_type &pits(l.pits());

	for (const level::position_type &pit: pits) {
		if (!std::get<0>(tiles[pit.second][pit.first].rock())) {
			return false;
		}
	}

	return true;
}

} // namespace sokoban
