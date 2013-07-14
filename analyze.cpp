#include <algorithm>
#include <set>

#include "analyze.h"
#include "level.h"

namespace sokoban {

bool
is_win(const level &l)
{
	const level::positions_type &pits(l.pits());
	const level::positions_type &rocks(l.rocks());

	return std::includes(
		rocks.begin(),
		rocks.end(),
		pits.begin(),
		pits.end());
}

} // namespace sokoban
