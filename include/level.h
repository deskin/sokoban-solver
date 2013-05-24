#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <set>
#include <string>
#include <utility>

namespace sokoban {

class level {
public:
	typedef std::pair<size_t, size_t> position_type;
	typedef std::set<position_type> positions_type;

	level() :
		is_parsed(false),
		avatar_position(0, 0),
		pit_locations(),
		rock_locations()
	{}

	const position_type &avatar() const
	{
		return require_parsed_or_throw(avatar_position);
	}

	const positions_type &pits() const
	{
		return require_parsed_or_throw(pit_locations);
	}

	const positions_type &rocks() const
	{
		return require_parsed_or_throw(rock_locations);
	}

	void parse(const std::string &s);

private:
	bool is_parsed;
	position_type avatar_position;
	positions_type pit_locations;
	positions_type rock_locations;

	template <typename T>
	const T &require_parsed_or_throw(const T &val) const
	{
		if (!is_parsed) {
			throw level_not_loaded();
		}

		return val;
	}


};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
