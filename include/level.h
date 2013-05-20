#ifndef SOKOBAN_LEVEL_H_
#define SOKOBAN_LEVEL_H_

#include <string>

namespace sokoban {

class level {
public:
	void parse(const std::string &s);
};

} // namespace sokoban

#endif // SOKOBAN_LEVEL_H_
