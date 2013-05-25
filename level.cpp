#include <string>
#include "errors.h"
#include "level.h"

namespace sokoban {

void
level::parse(const std::string &s)
{
	size_t avatar_count = 0;
	size_t column = 0;
	size_t row = 0;

	for (const char &c : s) {
		if (c == '@' || c == '7') {
			++avatar_count;
			avatar_position.first = column;
			avatar_position.second = row;
		}

		if (c == '`' || c == '6') {
			rock_locations.insert(std::make_pair(column, row));
		}

		if (c == '^' || c == '6' || c == '7') {
			pit_locations.insert(std::make_pair(column, row));
		}

		if (c == '\n') {
			++row;
			column = 0;
		} else {
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

	is_parsed = true;
}

} // namespace sokoban
