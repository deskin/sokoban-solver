#include <string>
#include <vector>

#include "analyze.h"
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
simulator::win() const
{
	if (!has_run) {
		throw simulator_not_run();
	}

	return is_win(level_steps.back());
}

void
simulator::run()
{
	has_run = true;
}

} // namespace sokoban
