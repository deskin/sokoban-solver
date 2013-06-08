#ifndef SOKOBAN_MOVE_H_
#define SOKOBAN_MOVE_H_

#include <type_traits>

#include "level.h"

namespace sokoban {

namespace direction {

enum class value {
	up,
	right,
	down,
	left
};

typedef std::integral_constant<value, value::up> up;
typedef std::integral_constant<value, value::right> right;
typedef std::integral_constant<value, value::down> down;
typedef std::integral_constant<value, value::left> left;

} // namespace direction

bool can_move(const level &l, direction::up);
bool can_move(const level &l, direction::right);
bool can_move(const level &l, direction::down);
bool can_move(const level &l, direction::left);

} // namespace sokoban

#endif // SOKOBAN_MOVE_H_
