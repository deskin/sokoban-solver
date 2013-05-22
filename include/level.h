#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <string>
#include <utility>

namespace sokoban {

class level {
public:
	level() :
		avatar_position(0, 0)
	{}

	const std::pair<size_t, size_t> &avatar() const
	{
		return avatar_position;
	}

	void parse(const std::string &s);

private:
	std::pair<size_t, size_t> avatar_position;
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
