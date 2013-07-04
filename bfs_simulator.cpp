#include <string>
#include <vector>

#include "bfs_simulator.h"

namespace sokoban {

bfs_simulator::bfs_simulator(const std::string &s) :
	level_steps()
{
	level_steps.emplace_back();
	level_steps[0].parse(s);
}

} // namespace sokoban
