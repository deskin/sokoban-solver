#include <string>
#include "errors.h"
#include "level.h"

namespace sokoban {

void
level::parse(const std::string &s)
{
	size_t avatar_count = 0;
	size_t rock_count = 0;
	size_t column = 0;
	size_t row = 0;

	for (const char &c : s) {
		if (c == '@') {
			++avatar_count;
			avatar_position.first = column;
			avatar_position.second = row;
		} else if (c == '`') {
			++rock_count;
		} else if (c == '^') {
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

	if (rock_count < pit_locations.size()) {
		throw level_parse_exception();
	}

	level_is_parsed = true;
}

} // namespace sokoban
