#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <ostream>
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

	bool operator==(const level &rhs) const;

	bool operator!=(const level &rhs) const { return !(*this == rhs); }

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
		has_avatar(false),
		pit_pointer(false, pointer_type()),
		rock_pointer(false, pointer_type())
	{}

	bool is_valid() const { return valid; }

	bool avatar() const;

	void set_avatar();

	void unset_avatar();

	const pointer_tuple &pit() const;

	void set_pit(pointer_type i);

	void unset_pit();

	const pointer_tuple &rock() const;

	void set_rock(pointer_type i);

	void unset_rock();

	template <template <typename> class Traits>
	friend
	std::basic_ostream<char, Traits<char> > &
	operator<<(std::basic_ostream<char, Traits<char> > &os, const tile &t);

private:
	bool valid;
	bool has_avatar;
	pointer_tuple pit_pointer;
	pointer_tuple rock_pointer;

	template <template <typename> class Traits>
	void
	ostream_insert(std::basic_ostream<char, Traits<char> > &os) const
	{
		if (!valid) {
			os << ' ';
		} else if (std::get<0>(pit_pointer)) {
			if (has_avatar) {
				os << '7';
			} else if (std::get<0>(rock_pointer)) {
				os << '6';
			} else {
				os << '^';
			}
		} else if (std::get<0>(rock_pointer)) {
			os << '`';
		} else if (has_avatar) {
			os << '@';
		} else {
			os << '.';
		}
	}
};

private:
	bool is_parsed;
	position_type avatar_position;
	positions_type pit_locations;
	positions_type rock_locations;
	tiles_type tile_array;
};

template <template <typename> class Traits>
std::basic_ostream<char, Traits<char> > &
operator<<(std::basic_ostream<char, Traits<char> > &os, const level::tile &t)
{
	t.ostream_insert(os);
	return os;
}

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
