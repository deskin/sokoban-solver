#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "errors.h"
#include "level.h"

namespace {

template <typename T>
const T &
require_parsed_or_throw(const T &val, bool is_parsed)
{
	if (!is_parsed) {
		throw sokoban::level_not_loaded();
	}

	return val;
}

} // namespace

namespace sokoban {

const level::position_type &
level::avatar() const
{
	return require_parsed_or_throw(avatar_position, is_parsed);
}

const level::positions_type &
level::pits() const
{
	return require_parsed_or_throw(immutable_data->pits, is_parsed);
}

const level::positions_type &
level::rocks() const
{
	return require_parsed_or_throw(*rock_locations, is_parsed);
}

const level::tiles_type &
level::tiles() const
{
	return require_parsed_or_throw(immutable_data->tiles, is_parsed);
}

void
level::parse(const std::string &s)
{
	size_t avatar_count = 0;
	size_t column = 0;
	size_t row = 0;

	std::shared_ptr<const_data> data = std::make_shared<const_data>();
	data->tiles.emplace_back();
	rock_locations = std::make_shared<positions_type>();

	for (const char &c : s) {
		if (c == '\n') {
			if (data->tiles[row].size() == 0) {
				throw level_parse_exception();
			}

			++row;
			column = 0;
			data->tiles.emplace_back();
		} else {
			bool valid_symbol = (c == ' ');

			data->tiles[row].push_back(!valid_symbol);

			if (c == '@' || c == '7') {
				valid_symbol = true;
				++avatar_count;
				avatar_position.first = column;
				avatar_position.second = row;
			}

			if (c == '`' || c == '6') {
				valid_symbol = true;
				rock_locations->insert(std::make_pair(
					column,
					row));
			}

			if (c == '^' || c == '6' || c == '7') {
				valid_symbol = true;
				data->pits.insert(std::make_pair(
					column,
					row));
			}

			if (!valid_symbol && c != '.') {
				throw level_parse_exception();
			}

			++column;
		}
	}

	if (avatar_count != 1) {
		throw level_parse_exception();
	}

	if (rock_locations->size() < data->pits.size()) {
		throw level_parse_exception();
	}

	if (0 == data->pits.size()) {
		throw level_parse_exception();
	}

	if (data->tiles[row].size() == 0) {
		data->tiles.pop_back();
	}

	is_parsed = true;

	immutable_data = data;
}

void
level::move_avatar(const level::position_type &new_position)
{
	avatar_position = new_position;
}

void
level::move_rock(
	const level::position_type &old_position,
	const level::position_type &new_position)
{
	if (!rock_locations.unique()) {
		std::shared_ptr<positions_type> ptr =
			std::make_shared<positions_type>(*rock_locations);
		{
			using std::swap;
			swap(ptr, rock_locations);
		}
	}

	positions_type::const_iterator rock(
		rock_locations->find(old_position));
		rock_locations->insert(rock, new_position);
	rock_locations->erase(rock);
}

bool
level::operator==(const level &rhs) const
{
	return (avatar_position == rhs.avatar_position) &&
		(rock_locations == rhs.rock_locations ||
		*rock_locations == *rhs.rock_locations);
}

bool
level::operator<(const level &rhs) const
{
	return avatar_position < rhs.avatar_position ||
		(avatar_position == rhs.avatar_position &&
		rock_locations != rhs.rock_locations &&
		*rock_locations < *rhs.rock_locations);
}

} // namespace sokoban
