#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "level.h"
#include "move.h"

BOOST_AUTO_TEST_SUITE(move)

BOOST_AUTO_TEST_CASE(can_move_basic) {
	sokoban::level level;
	std::string s(
		"^`...\n"
		"  .@.\n"
		"  ...\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::up()));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::right()));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::down()));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::left()));
}

BOOST_AUTO_TEST_SUITE_END()
