#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <set>
#include <string>
#include <utility>

#include "errors.h"

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

	const position_type &avatar() const;

	const positions_type &pits() const;

	const positions_type &rocks() const;

	void parse(const std::string &s);

class tile {
public:
	enum class kind {
		invalid,
		valid
	};

	explicit tile(kind) {}

	positions_type::iterator pit() const
	{
		throw tile_invalid_exception();
	}

	positions_type::iterator
	set_pit(level::positions_type::iterator i)
	{
		throw tile_invalid_exception();
	}
};

private:
	bool is_parsed;
	position_type avatar_position;
	positions_type pit_locations;
	positions_type rock_locations;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
