#ifndef SOKOBAN_LEVEL_MOVER_H_
#define SOKOBAN_LEVEL_MOVER_H_

#include <vector>

#include "level.h"
#include "move.h"

namespace sokoban {

class level_mover {
	typedef std::vector<level> levels_container;
	levels_container levels;

public:
	typedef levels_container::const_iterator iterator;

	explicit level_mover(const level &l);

	iterator begin() const { return levels.cbegin(); }

	iterator end() const { return levels.cend(); }

	size_t size() const { return levels.size(); }
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_MOVER_H_
