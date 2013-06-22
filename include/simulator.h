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

public:
	explicit simulator(const std::string &) :
		level_steps()
	{}

	const steps_type &steps() const { return level_steps; }
};

} // namespace sokoban

#endif // SOKOBAN_SIMULATOR_H_
