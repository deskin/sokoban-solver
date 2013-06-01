#include <set>
#include <string>
#include <utility>
#include <vector>

#include "errors.h"
#include "level.h"

namespace {

template <typename T>
const T &require_parsed_or_throw(const T &val, bool is_parsed)
{
	if (!is_parsed) {
		throw sokoban::level_not_loaded();
	}

	return val;
}

} // namespace (anonymous)

namespace sokoban {

const level::position_type &
level::avatar() const
{
	return require_parsed_or_throw(avatar_position, is_parsed);
}

const level::positions_type &
level::pits() const
{
	return require_parsed_or_throw(pit_locations, is_parsed);
}

const level::positions_type &
level::rocks() const
{
	return require_parsed_or_throw(rock_locations, is_parsed);
}

const level::tiles_type &
level::tiles() const
{
	return require_parsed_or_throw(tile_array, is_parsed);
}

void
level::parse(const std::string &s)
{
	size_t avatar_count = 0;
	size_t column = 0;
	size_t row = 0;

	tile_array.emplace_back();

	for (const char &c : s) {

		if (c == '\n') {
			++row;
			column = 0;
			tile_array.emplace_back();
		} else {
			tile_array[row].emplace_back(
				c == ' ' ?
					tile::kind::invalid :
					tile::kind::valid);
			if (c == '@' || c == '7') {
				++avatar_count;
				avatar_position.first = column;
				avatar_position.second = row;
			}

			if (c == '`' || c == '6') {
				tile_array[row][column].set_rock(
					rock_locations.insert(
						std::make_pair(
							column,
							row)).first);
			}

			if (c == '^' || c == '6' || c == '7') {
				tile_array[row][column].set_pit(
					pit_locations.insert(
						std::make_pair(
							column,
							row)).first);
			}

			++column;
		}
	}

	if (avatar_count != 1) {
		throw level_parse_exception();
	}

	if (rock_locations.size() < pit_locations.size()) {
		throw level_parse_exception();
	}

	if (0 == pit_locations.size()) {
		throw level_parse_exception();
	}

	if (tile_array[row].size() == 0) {
		tile_array.pop_back();
	}

	is_parsed = true;
}

} // namespace sokoban
