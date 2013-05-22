#include <string>
#include "errors.h"
#include "level.h"

namespace sokoban {

void
level::parse(const std::string &s)
{
	size_t avatar_count = 0;
	size_t pit_count = 0;
	size_t rock_count = 0;
	size_t column = 0;
	size_t row = 0;

	for (const char &c : s) {
		if (c == '@') {
			if (avatar_count != 0) {
				throw level_parse_exception();
			}

			++avatar_count;
			avatar_position.first = row;
			avatar_position.second = column;
		} else if (c == '`') {
			++rock_count;
		} else if (c == '^') {
			++pit_count;
		}

		if (c == '\n') {
			++column;
			row = 0;
		} else {
			++row;
		}
	}

	if (avatar_count != 1) {
		throw level_parse_exception();
	}

	if (rock_count < pit_count) {
		throw level_parse_exception();
	}
}

} // namespace sokoban
