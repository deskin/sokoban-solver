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
	typedef levels_container::iterator iterator;
	typedef levels_container::const_iterator const_iterator;

	explicit level_mover(const level &l);

	iterator begin() { return levels.begin(); }

	const_iterator begin() const { return cbegin(); }

	const_iterator cbegin() const { return levels.cbegin(); }

	iterator end() { return levels.end(); }

	const_iterator end() const { return cend(); }

	const_iterator cend() const { return levels.cend(); }

	size_t size() const { return levels.size(); }
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_MOVER_H_
