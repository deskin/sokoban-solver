#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <set>
#include <string>
#include <utility>

namespace sokoban {

class level {
public:
	typedef std::pair<size_t, size_t> position_type;

	level() :
		level_is_parsed(false),
		avatar_position(0, 0),
		pit_locations()
	{}

	const position_type &avatar() const
	{
		if (!level_is_parsed) {
			throw level_not_loaded();
		}

		return avatar_position;
	}

	const std::set<position_type> &pits()
	{
		return pit_locations;
	}

	void parse(const std::string &s);

private:
	bool level_is_parsed;
	position_type avatar_position;
	std::set<position_type> pit_locations;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
