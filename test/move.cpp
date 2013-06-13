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

BOOST_AUTO_TEST_CASE(can_move_rock) {
	sokoban::level level;
	std::string s(
		".....\n"
		"^.`..\n"
		".`@`.\n"
		"..`..\n"
		".....\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::up()));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::right()));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::down()));
	BOOST_CHECK(sokoban::can_move(level, sokoban::direction::left()));
}

BOOST_AUTO_TEST_CASE(cannot_move_wall) {
	sokoban::level level;
	sokoban::level level2;
	std::string s(
		"^`...\n"
		"   @.\n"
		"    .\n");
	std::string s2(
		".    \n"
		".@   \n"
		"...`^\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s2));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::down()));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::left()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::up()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::right()));
}

BOOST_AUTO_TEST_CASE(cannot_move_boundary) {
	sokoban::level level;
	sokoban::level level2;
	std::string s(
		"^`..\n"
		"  .@\n");
	std::string s2(
		"@.  \n"
		"..`^\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s2));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::down()));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::right()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::up()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::left()));
}

BOOST_AUTO_TEST_CASE(cannot_move_rock_blocked_wall) {
	sokoban::level level;
	sokoban::level level2;
	std::string s(
		"^`.\n"
		"`@.\n");
	std::string s2(
		".@`\n"
		".`^\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s2));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::up()));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::left()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::down()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::right()));
}

BOOST_AUTO_TEST_CASE(cannot_move_rock_blocked_rock) {
	sokoban::level level;
	sokoban::level level2;
	std::string s(
		"..`.\n"
		".^`.\n"
		"``@.\n");
	std::string s2(
		".@``\n"
		".`^.\n"
		".`..\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s2));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::up()));
	BOOST_CHECK(!sokoban::can_move(level, sokoban::direction::left()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::down()));
	BOOST_CHECK(!sokoban::can_move(level2, sokoban::direction::right()));
}

BOOST_AUTO_TEST_CASE(get_level) {
	sokoban::level level;
	sokoban::level level2;
	std::string s(
		"^`.\n"
		"@..\n");
	std::string s2(
		"7`.\n"
		"...\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s2));
	BOOST_CHECK_EQUAL(
		level2,
		sokoban::move(level, sokoban::direction::up()));
}

BOOST_AUTO_TEST_SUITE_END()
