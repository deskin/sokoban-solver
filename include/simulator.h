#ifndef SOKOBAN_SIMULATOR_H_
#define SOKOBAN_SIMULATOR_H_

#include <string>
#include <vector>

#include "level.h"

namespace detail {

enum class solve_status {
	too_deep,
	pruned,
	win
};

} // namespace detail

namespace sokoban {

class simulator {
public:
	typedef std::vector<level> steps_type;

private:
	steps_type level_steps;
	size_t solve_call_count;
	bool has_run;

	::detail::solve_status solve(size_t max_steps);

public:
	explicit simulator(const std::string &s);

	bool win() const;

	size_t solve_calls() const { return solve_call_count; }

	const steps_type &steps() const { return level_steps; }

	void run();
};

} // namespace sokoban

#endif // SOKOBAN_SIMULATOR_H_
