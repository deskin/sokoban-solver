#ifndef SOKOBAN_ERRORS_H_
#define SOKOBAN_ERRORS_H_

#include <exception>

namespace sokoban {

class cannot_move_exception : public std::exception {};

class level_parse_exception : public std::exception {};

class level_not_loaded : public std::exception {};

class tile_invalid_exception : public std::exception {};

} // namespace sokoban

#endif //SOKOBAN_ERRORS_H_
