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
	sokoban::level level_up;
	sokoban::level level_right;
	sokoban::level level_down;
	sokoban::level level_left;
	std::string s(
		" ^`.\n"
		".@..\n"
		" .  \n");
	std::string s_up(
		" 7`.\n"
		"....\n"
		" .  \n");
	std::string s_right(
		" ^`.\n"
		"..@.\n"
		" .  \n");
	std::string s_down(
		" ^`.\n"
		"....\n"
		" @  \n");
	std::string s_left(
		" ^`.\n"
		"@...\n"
		" .  \n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level_up.parse(s_up));
	BOOST_REQUIRE_NO_THROW(level_right.parse(s_right));
	BOOST_REQUIRE_NO_THROW(level_down.parse(s_down));
	BOOST_REQUIRE_NO_THROW(level_left.parse(s_left));
	BOOST_CHECK_EQUAL(
		level_up,
		sokoban::move(level, sokoban::direction::up()));
	BOOST_CHECK_EQUAL(
		level_right,
		sokoban::move(level, sokoban::direction::right()));
	BOOST_CHECK_EQUAL(
		level_down,
		sokoban::move(level, sokoban::direction::down()));
	BOOST_CHECK_EQUAL(
		level_left,
		sokoban::move(level, sokoban::direction::left()));
}

BOOST_AUTO_TEST_CASE(get_level_rock) {
	sokoban::level level;
	sokoban::level level_up;
	sokoban::level level_right;
	sokoban::level level_down;
	sokoban::level level_left;
	std::string s(
		"  ^  \n"
		"  `  \n"
		".`@`.\n"
		"  `  \n"
		"  .  \n");
	std::string s_up(
		"  6  \n"
		"  @  \n"
		".`.`.\n"
		"  `  \n"
		"  .  \n");
	std::string s_right(
		"  ^  \n"
		"  `  \n"
		".`.@`\n"
		"  `  \n"
		"  .  \n");
	std::string s_down(
		"  ^  \n"
		"  `  \n"
		".`.`.\n"
		"  @  \n"
		"  `  \n");
	std::string s_left(
		"  ^  \n"
		"  `  \n"
		"`@.`.\n"
		"  `  \n"
		"  .  \n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level_up.parse(s_up));
	BOOST_REQUIRE_NO_THROW(level_right.parse(s_right));
	BOOST_REQUIRE_NO_THROW(level_down.parse(s_down));
	BOOST_REQUIRE_NO_THROW(level_left.parse(s_left));
	sokoban::level l(sokoban::move(level, sokoban::direction::up()));
	BOOST_CHECK_EQUAL(level_up.rocks().size(), l.rocks().size());
	auto &r = l.rocks();
	auto &r_up = level_up.rocks();
	size_t x = 0;
	for (auto i = r.cbegin(), i_up = r_up.cbegin();
		i != r.cend() && i_up != r_up.cend();
		++i, ++i_up) {
		BOOST_CHECK_EQUAL(x * 100 + i_up->first * 10 + i_up->second,
			x * 100 + i->first * 10 + i->second);
		BOOST_CHECK_EQUAL(i_up->second, i->second);
		++x;
	}
	BOOST_CHECK(
		level_up.rocks() == l.rocks());
	BOOST_CHECK(
		level_up.avatar() == l.avatar());
	BOOST_CHECK_EQUAL(
		level_right,
		sokoban::move(level, sokoban::direction::right()));
	BOOST_CHECK_EQUAL(
		level_down,
		sokoban::move(level, sokoban::direction::down()));
	BOOST_CHECK_EQUAL(
		level_left,
		sokoban::move(level, sokoban::direction::left()));
}

BOOST_AUTO_TEST_SUITE_END()
