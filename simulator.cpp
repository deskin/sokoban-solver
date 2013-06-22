#include <string>
#include <vector>

#include "level.h"
#include "simulator.h"

namespace sokoban {

simulator::simulator(const std::string &s) :
	level_steps(1)
{
	level_steps[0].parse(s);
}

} // namespace sokoban
