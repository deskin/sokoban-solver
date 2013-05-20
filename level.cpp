#include <string>
#include "errors.h"
#include "level.h"

namespace sokoban {

void
level::parse(const std::string &s)
{
	size_t avatar_count = 0;

	for (const char &c : s) {
		if (c == '@') {
			++avatar_count;
		}
	}

	if (avatar_count > 1) {
		throw level_parse_exception();
	}
}

} // namespace sokoban
