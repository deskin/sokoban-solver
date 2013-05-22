#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <string>
#include <utility>

namespace sokoban {

class level {
public:
	typedef std::pair<size_t, size_t> position_type;

	level() :
		avatar_position(0, 0)
	{}

	const position_type &avatar() const
	{
		return avatar_position;
	}

	void parse(const std::string &s);

private:
	position_type avatar_position;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
