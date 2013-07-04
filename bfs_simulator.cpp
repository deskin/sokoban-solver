#include <string>
#include <vector>

#include "analyze.h"
#include "bfs_simulator.h"
#include "errors.h"

namespace sokoban {

bfs_simulator::bfs_simulator(const std::string &s) :
	level_steps()
{
	level_steps.emplace_back();
	level_steps[0].parse(s);
}

bool
bfs_simulator::win() const
{
	if (!has_run) {
		throw simulator_not_run();
	}

	return is_win(level_steps.back());
}

void
bfs_simulator::run()
{
	has_run = true;
}
} // namespace sokoban
