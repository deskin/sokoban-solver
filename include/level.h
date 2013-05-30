#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <set>
#include <string>
#include "tuple-hack.h"
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

	const position_type &avatar() const;

	const positions_type &pits() const;

	const positions_type &rocks() const;

	void parse(const std::string &s);

class tile {
public:
	typedef positions_type::iterator pointer_type;

	enum class kind {
		invalid,
		valid
	};

	explicit tile(kind k) :
		valid(kind::valid == k),
		pit_valid(false),
		rock_valid(false),
		pit_pointer(),
		rock_pointer()
	{}

	std::tuple<bool, pointer_type> pit() const;

	pointer_type set_pit(pointer_type i);

	void unset_pit();

	std::tuple<bool, pointer_type> rock() const;

	pointer_type set_rock(pointer_type i);

	void unset_rock();

private:
	bool valid;
	bool pit_valid;
	bool rock_valid;
	pointer_type pit_pointer;
	pointer_type rock_pointer;
};

private:
	bool is_parsed;
	position_type avatar_position;
	positions_type pit_locations;
	positions_type rock_locations;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
