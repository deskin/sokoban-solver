#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <set>
#include <string>
#include "tuple-hack.h"
#include <utility>
#include <vector>

namespace sokoban {

class level {
public:
	class tile;
	typedef std::pair<size_t, size_t> position_type;
	typedef std::set<position_type> positions_type;
	typedef std::vector<std::vector<tile>> tiles_type;

	level() :
		is_parsed(false),
		avatar_position(0, 0),
		pit_locations(),
		rock_locations(),
		tile_array()
	{}

	const position_type &avatar() const;

	const positions_type &pits() const;

	const positions_type &rocks() const;

	const tiles_type &tiles() const;

	void parse(const std::string &s);

class tile {
public:
	typedef positions_type::iterator pointer_type;
	typedef std::tuple<bool, pointer_type> pointer_tuple;

	enum class kind {
		invalid,
		valid
	};

	explicit tile(kind k) :
		valid(kind::valid == k),
		pit_pointer(false, pointer_type()),
		rock_pointer(false, pointer_type())
	{}

	bool is_valid() const { return valid; }

	const pointer_tuple &pit() const;

	void set_pit(pointer_type i);

	void unset_pit();

	const pointer_tuple &rock() const;

	void set_rock(pointer_type i);

	void unset_rock();

private:
	bool valid;
	pointer_tuple pit_pointer;
	pointer_tuple rock_pointer;
};

private:
	bool is_parsed;
	position_type avatar_position;
	positions_type pit_locations;
	positions_type rock_locations;
	tiles_type tile_array;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
