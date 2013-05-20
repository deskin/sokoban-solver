#ifndef SOKOBAN_ERRORS_H_
#define SOKOBAN_ERRORS_H_

#include <exception>

namespace sokoban {

class level_parse_exception : public std::exception {};

} // namespace sokoban

#endif //SOKOBAN_ERRORS_H_
