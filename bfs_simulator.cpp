#include <map>
#include <string>
#include <utility>
#include <vector>

#include "analyze.h"
#include "bfs_simulator.h"
#include "errors.h"
#include "level_mover.h"

namespace sokoban {

bfs_simulator::bfs_simulator(const std::string &s) :
	level_steps(),
	has_run(false),
	move_count(0)
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
	std::vector<map_type::iterator> initial_set;
	map_type odds;
	std::vector<map_type::iterator> odd_set;

	auto i = evens.insert(std::make_pair(level_steps[0],
		detail::level_pointer()));
	initial_set.emplace_back(std::move(i).first);

	solve(evens, odds, initial_set, odd_set);
}

bool
bfs_simulator::solve(bfs_simulator::map_type &current,
	bfs_simulator::map_type &next,
	std::vector<bfs_simulator::map_type::iterator> &current_set,
	std::vector<bfs_simulator::map_type::iterator> &next_set)
{
	for (const map_type::iterator &i : current_set) {
		if (is_win(i->first)) {
			fill_steps(i);
			return true;
		} else {
			level_mover mover(i->first);

			for (level &l: mover) {
				++move_count;
				map_type::iterator n = next.lower_bound(l);

				if (n == next.end() || n->first != l) {
					n = next.insert(n, std::make_pair(l,
						detail::level_pointer(i)));
					next_set.emplace_back(std::move(n));
				}
			}
		}
	}

	if (next_set.size() == 0) {
		return false;
	}

	current_set.resize(0);

	return solve(next, current, next_set, current_set);
}

void
bfs_simulator::fill_steps(const bfs_simulator::map_type::const_iterator &i)
{
	if (i->second.empty()) {
		return;
	}

	fill_steps(i->second.get());

	level_steps.push_back(i->first);
}

} // namespace sokoban
