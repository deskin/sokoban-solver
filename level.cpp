#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "errors.h"
#include "level.h"

#include "deskin/shared_ptr_cow.h"

namespace cow = deskin::copy_on_write;

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
	return require_parsed_or_throw(*pit_locations, is_parsed);
}

const level::positions_type &
level::rocks() const
{
	return require_parsed_or_throw(*rock_locations, is_parsed);
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

	tile_array.emplace_back(
		std::make_shared<std::vector<std::shared_ptr<tile>>>());
	pit_locations = std::make_shared<positions_type>();
	rock_locations = std::make_shared<positions_type>();

	for (const char &c : s) {
		if (c == '\n') {
			if (tile_array[row]->size() == 0) {
				throw level_parse_exception();
			}

			++row;
			column = 0;
			tile_array.emplace_back(
				std::make_shared<
					std::vector<std::shared_ptr<tile>>>());
		} else {
			bool valid_symbol = (c == ' ');

			tile_array[row]->emplace_back(std::make_shared<tile>(
				valid_symbol ?
					tile::kind::invalid :
					tile::kind::valid));

			if (c == '@' || c == '7') {
				valid_symbol = true;
				++avatar_count;
				avatar_position.first = column;
				avatar_position.second = row;
				(*tile_array[row])[column]->set_avatar();
			}

			if (c == '`' || c == '6') {
				valid_symbol = true;
				(*tile_array[row])[column]->set_rock(
					rock_locations->insert(
						std::make_pair(
							column,
							row)).first);
			}

			if (c == '^' || c == '6' || c == '7') {
				valid_symbol = true;
				(*tile_array[row])[column]->set_pit(
					pit_locations->insert(
						std::make_pair(
							column,
							row)).first);
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

	if (rock_locations->size() < pit_locations->size()) {
		throw level_parse_exception();
	}

	if (0 == pit_locations->size()) {
		throw level_parse_exception();
	}

	if (tile_array[row]->size() == 0) {
		tile_array.pop_back();
	}

	is_parsed = true;
}

void
level::move_avatar(const level::position_type &new_position)
{
	cow::copy_if_shared((*cow::copy_if_shared(
		tile_array[avatar_position.second]))[avatar_position.first])
			->unset_avatar();
	cow::copy_if_shared((*cow::copy_if_shared(
		tile_array[new_position.second]))[new_position.first])
			->set_avatar();
	avatar_position = new_position;
}

void
level::move_rock(
	const level::position_type &old_position,
	const level::position_type &new_position)
{
	if (!rock_locations.unique()) {
		cow::copy_shared(rock_locations);

		for (positions_type::iterator i = rock_locations->begin();
			i != rock_locations->end();
			++i) {
			cow::copy_if_shared((*cow::copy_if_shared(
				tile_array[i->second]))[i->first])
					->set_rock(i);
		}
	}

	const tile::pointer_tuple &rock(
		(*tile_array[old_position.second])[old_position.first]
			->rock());
	cow::copy_if_shared((*cow::copy_if_shared(
		tile_array[new_position.second]))[new_position.first])
			->set_rock(rock_locations->insert(
				std::get<1>(rock),
				new_position));
	rock_locations->erase(std::get<1>(rock));
	cow::copy_if_shared((*cow::copy_if_shared(
		tile_array[old_position.second]))[old_position.first])
			->unset_rock();
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
