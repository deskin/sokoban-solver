#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <string>
#include <utility>

namespace sokoban {

class level {
public:
	typedef std::pair<size_t, size_t> position_type;

	level() :
		level_is_parsed(false),
		avatar_position(0, 0)
	{}

	const position_type &avatar() const
	{
		if (!level_is_parsed) {
			throw level_not_loaded();
		}

		return avatar_position;
	}

	void parse(const std::string &s);

private:
	bool level_is_parsed;
	position_type avatar_position;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
