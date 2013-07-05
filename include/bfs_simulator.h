#ifndef SOKOBAN_BFS_SIMULATOR_H_
#define SOKOBAN_BFS_SIMULATOR_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "level.h"

namespace sokoban {

namespace detail {

class level_pointer;

typedef std::map<level, level_pointer> bfs_map_type;

class level_pointer {
public:
	typedef bfs_map_type::iterator value_type;

	level_pointer() :
		i(),
		is_empty(true)
	{}

	explicit level_pointer(value_type i) :
		i(i),
		is_empty(false)
	{}

private:
	value_type i;
	bool is_empty;
};

} // namespace detail

class bfs_simulator {
private:
	typedef detail::bfs_map_type map_type;
	typedef std::set<level> set_type;

public:
	typedef std::vector<level> steps_type;

	explicit bfs_simulator(const std::string &s);

	const steps_type &steps() const { return level_steps; }

	bool win() const;

	void run();

private:
	steps_type level_steps;
	bool has_run;

	bool solve(map_type &current,
		map_type &next,
		set_type &current_set,
		set_type &next_set);
};

} // namespace sokoban

#endif // SOKOBAN_BFS_SIMULATOR_H_
