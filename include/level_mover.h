#ifndef SOKOBAN_LEVEL_MOVER_H_
#define SOKOBAN_LEVEL_MOVER_H_

#include <vector>

#include "level.h"
#include "move.h"

namespace sokoban {

class level_mover {
	std::vector<level> levels;

public:
	level_mover(const level &l);

	size_t size() const { return levels.size(); }
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_MOVER_H_
