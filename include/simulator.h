#ifndef SOKOBAN_SIMULATOR_H_
#define SOKOBAN_SIMULATOR_H_

#include <string>
#include <vector>

#include "level.h"

namespace sokoban {

class simulator {
public:
	typedef std::vector<level> steps_type;

private:
	steps_type level_steps;
	bool has_run;

public:
	explicit simulator(const std::string &s);

	bool is_win() const;

	const steps_type &steps() const { return level_steps; }

	void run();
};

} // namespace sokoban

#endif // SOKOBAN_SIMULATOR_H_
