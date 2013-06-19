#ifndef SOKOBAN_LEVEL_MOVER_H_
#define SOKOBAN_LEVEL_MOVER_H_

#include <vector>

#include "level.h"

namespace sokoban {

class level_mover {
public:
	level_mover(const level &l) {}

	size_t size() const { return 1; }
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_MOVER_H_
