#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <memory>
#include <ostream>
#include <set>
#include <string>
#include "tuple-hack.h"
#include <utility>
#include <vector>

namespace sokoban {

class level {
public:
	typedef std::pair<size_t, size_t> position_type;
	typedef std::set<position_type> positions_type;
	typedef std::vector<std::vector<bool> > tiles_type;

	level() :
		is_parsed(false),
		avatar_position(0, 0),
		immutable_data(),
		rock_locations()
	{}

	level(const level &) = default;

	level(level &&) = default;

	const position_type &avatar() const;

	const positions_type &pits() const;

	const positions_type &rocks() const;

	const tiles_type &tiles() const;

	void move_avatar(const position_type &new_position);

	void move_rock(
		const position_type &old_position,
		const position_type &new_position);

	void parse(const std::string &s);

	level &operator=(const level &) = default;

	level &operator=(level &&) = default;

	bool operator==(const level &rhs) const;

	bool operator<(const level &rhs) const;

	bool operator!=(const level &rhs) const { return !(*this == rhs); }

	template <template <typename> class Traits>
	friend
	std::basic_ostream<char, Traits<char> > &
	operator<<(std::basic_ostream<char, Traits<char> > &os, const level &l);

private:
	struct const_data {
		positions_type pits;
		tiles_type tiles;
	};

	bool is_parsed;
	position_type avatar_position;
	std::shared_ptr<const const_data> immutable_data;
	std::shared_ptr<positions_type> rock_locations;

	template <template <typename> class Traits>
	void
	ostream_insert(std::basic_ostream<char, Traits<char> > &os) const
	{
		for (size_t r = 0; r < immutable_data->tiles.size(); ++r) {
			const std::vector<bool> &v = immutable_data->tiles[r];
			for (size_t c = 0; c < v.size(); ++c) {
				if (!v[c]) {
					os << ' ';
				} else {
					const position_type loc =
						std::make_pair(c, r);
					if (pits().find(loc) !=
						pits().end()) {
						if (loc == avatar_position) {
							os << '7';
						} else if (rocks().find(loc) !=
							rocks().end()) {
							os << '6';
						} else {
							os << '^';
						}
					} else if (loc == avatar_position) {
						os << '@';
					} else if (rocks().find(loc) !=
						rocks().end()) {
						os << '`';
					} else {
						os << '.';
					}
				}
			}

			os << '\n';
		}
	}
};

template <template <typename> class Traits>
std::basic_ostream<char, Traits<char> > &
operator<<(std::basic_ostream<char, Traits<char> > &os, const level &l)
{
	l.ostream_insert(os);
	return os;
}

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
