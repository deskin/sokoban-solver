#include <string>
#include <vector>

#include "errors.h"
#include "level.h"
#include "simulator.h"

namespace sokoban {

simulator::simulator(const std::string &s) :
	level_steps(1),
	has_run(false)
{
	level_steps[0].parse(s);
}

bool
simulator::is_win() const
{
	if (!has_run) {
		throw simulator_not_run();
	}

	return true;
}

void
simulator::run()
{
	has_run = true;
}

} // namespace sokoban
