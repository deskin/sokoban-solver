#ifndef SOKOBAN_BFS_SIMULATOR_H_
#define SOKOBAN_BFS_SIMULATOR_H_

#include <string>
#include <vector>

#include "level.h"

namespace sokoban {

class bfs_simulator {
public:
	typedef std::vector<level> steps_type;

	explicit bfs_simulator(const std::string &);

	const steps_type &steps() const { return level_steps; }

private:
	steps_type level_steps;
};

} // namespace sokoban

#endif // SOKOBAN_BFS_SIMULATOR_H_
