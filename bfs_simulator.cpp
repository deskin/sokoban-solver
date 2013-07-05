#include <map>
#include <set>
#include <string>
#include <utility>
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
	map_type evens;
	std::set<level> initial_set;
	map_type odds;
	std::set<level> odd_set;

	evens.insert(std::make_pair(level_steps[0], level_pointer()));
	initial_set.insert(level_steps[0]);
}
bool
bfs_simulator::solve(bfs_simulator::map_type &current,
	bfs_simulator::map_type &next,
	bfs_simulator::set_type &current_set,
	bfs_simulator::set_type &next_set)
{

}

} // namespace sokoban
