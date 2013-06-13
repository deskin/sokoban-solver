#ifndef SOKOBAN_MOVE_H_
#define SOKOBAN_MOVE_H_

#include <type_traits>

#include "level.h"

#ifndef SOKOBAN_CAN_MOVE_DEFINED
#define SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION extern
#else
#define SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION
#endif

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

template <typename Direction>
bool can_move(const level &l, Direction);

SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION
template
bool can_move(const level &l, direction::up);

SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION
template
bool can_move(const level &l, direction::right);

SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION
template
bool can_move(const level &l, direction::down);

SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION
template
bool can_move(const level &l, direction::left);

level move(const level &l, direction::up);
level move(const level &l, direction::right);
level move(const level &l, direction::down);
level move(const level &l, direction::left);

} // namespace sokoban

#undef SOKOBAN_CAN_MOVE_TEMPLATE_INSTANTIATION

#endif // SOKOBAN_MOVE_H_
