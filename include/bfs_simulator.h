#ifndef SOKOBAN_BFS_SIMULATOR_H_
#define SOKOBAN_BFS_SIMULATOR_H_

#include <map>
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

	bool empty() const { return is_empty; }

	value_type get() const { return i; }

private:
	value_type i;
	bool is_empty;
};

} // namespace detail

class bfs_simulator {
private:
	typedef detail::bfs_map_type map_type;

public:
	typedef std::vector<level> steps_type;

	explicit bfs_simulator(const std::string &s);

	size_t solve_calls() const { return move_count; }

	const steps_type &steps() const { return level_steps; }

	bool win() const;

	void run();

private:
	steps_type level_steps;
	bool has_run;
	size_t move_count;

	bool solve(map_type &current,
		map_type &next,
		map_type &current_set,
		map_type &next_set);
	
	void fill_steps(const map_type::const_iterator &i);
};

} // namespace sokoban

#endif // SOKOBAN_BFS_SIMULATOR_H_
