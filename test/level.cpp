#define BOOST_TEST_MODULE sokoban tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include "tuple-hack.h"
#include <utility>
#include <vector>

#include "errors.h"
#include "level.h"

BOOST_AUTO_TEST_SUITE(level)

BOOST_AUTO_TEST_CASE(construct) {
	sokoban::level();
}

BOOST_AUTO_TEST_CASE(parse) {
	sokoban::level level;
	std::string s("@`^");
	BOOST_CHECK_NO_THROW(level.parse(s));
}

BOOST_AUTO_TEST_CASE(parse_too_many_avatars) {
	sokoban::level level;
	std::string s("@@`^");
	BOOST_CHECK_THROW(level.parse(s), sokoban::level_parse_exception);
}

BOOST_AUTO_TEST_CASE(parse_no_avatar) {
	sokoban::level level;
	std::string s("`^");
	BOOST_CHECK_THROW(level.parse(s), sokoban::level_parse_exception);
}

BOOST_AUTO_TEST_CASE(parse_not_enough_rocks) {
	sokoban::level level;
	std::string s("@`^^");
	BOOST_CHECK_THROW(level.parse(s), sokoban::level_parse_exception);
}

BOOST_AUTO_TEST_CASE(parse_get_avatar_0_0) {
	sokoban::level level;
	std::string s("@`^\n"
		      ".`^");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::position_type &pos(level.avatar());
	BOOST_CHECK_EQUAL(pos.first, 0);
	BOOST_CHECK_EQUAL(pos.second, 0);
}

BOOST_AUTO_TEST_CASE(parse_get_avatar_2_1) {
	sokoban::level level;
	std::string s("^`.\n"
		      "^`@");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::position_type &pos(level.avatar());
	BOOST_CHECK_EQUAL(pos.first, 2);
	BOOST_CHECK_EQUAL(pos.second, 1);
}

BOOST_AUTO_TEST_CASE(no_parse_avatar_throws) {
	sokoban::level level;
	BOOST_CHECK_THROW(level.avatar(), sokoban::level_not_loaded);
}

BOOST_AUTO_TEST_CASE(get_pits) {
	sokoban::level level;
	std::string s("@`^");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::positions_type &pits(level.pits());
	BOOST_CHECK(
		pits.cend() != std::find(
			pits.cbegin(),
			pits.cend(),
			std::make_pair<size_t, size_t>(2, 0)));
}

BOOST_AUTO_TEST_CASE(no_parse_pits_throws) {
	sokoban::level level;
	BOOST_CHECK_THROW(level.pits(), sokoban::level_not_loaded);
}

BOOST_AUTO_TEST_CASE(no_pits_throws) {
	sokoban::level level;
	std::string s("@.");
	BOOST_CHECK_THROW(level.parse(s), sokoban::level_parse_exception);
}

BOOST_AUTO_TEST_CASE(get_rocks) {
	sokoban::level level;
	std::string s("@. \n"
		      " ..\n"
		      "^`.");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::positions_type &rocks(level.rocks());
	BOOST_CHECK(
		rocks.cend() != std::find(
			rocks.cbegin(),
			rocks.cend(),
			std::make_pair<size_t, size_t>(1, 2)));

}

BOOST_AUTO_TEST_CASE(no_parse_rocks_throws) {
	sokoban::level level;
	BOOST_CHECK_THROW(level.rocks(), sokoban::level_not_loaded);
}

BOOST_AUTO_TEST_CASE(parse_combo_avatar) {
	sokoban::level level;
	std::string s("7`.\n"
		      "...");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::positions_type &pits(level.pits());
	BOOST_CHECK(
		pits.cend() != std::find(
			pits.cbegin(),
			pits.cend(),
			std::make_pair<size_t, size_t>(0, 0)));
	const sokoban::level::position_type &pos(level.avatar());
	BOOST_CHECK_EQUAL(pos.first, 0);
	BOOST_CHECK_EQUAL(pos.second, 0);
}

BOOST_AUTO_TEST_CASE(parse_combo_pit_rock) {
	sokoban::level level;
	std::string s("^.6.`.\n"
		      "   ..@");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::positions_type &pits(level.pits());
	BOOST_CHECK(
		pits.cend() != std::find(
			pits.cbegin(),
			pits.cend(),
			std::make_pair<size_t, size_t>(2, 0)));
	const sokoban::level::positions_type &rocks(level.rocks());
	BOOST_CHECK(
		rocks.cend() != std::find(
			rocks.cbegin(),
			rocks.cend(),
			std::make_pair<size_t, size_t>(2, 0)));
}

BOOST_AUTO_TEST_CASE(parse_get_tiles) {
	sokoban::level level;
	std::string s("^.6.`.\n"
		      "   ..@");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::tiles_type &tiles(level.tiles());
	BOOST_CHECK(tiles[0][3]);
	BOOST_CHECK(!tiles[1][0]);
}

BOOST_AUTO_TEST_CASE(tiles_end_not_empty) {
	sokoban::level level;
	std::string s("^.6.`.\n"
		      "   ..@\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	const sokoban::level::tiles_type &tiles(level.tiles());
	BOOST_CHECK_NE(tiles.rbegin()->size(), 0);
}

BOOST_AUTO_TEST_CASE(parse_tiles_not_empty) {
	sokoban::level level;
	std::string s(
		"\n"
		"^.6.`.\n"
		"\n"
		"   ..@\n");
	BOOST_CHECK_THROW(level.parse(s), sokoban::level_parse_exception);
}

BOOST_AUTO_TEST_CASE(equality) {
	sokoban::level level;
	sokoban::level level2;
	sokoban::level level3;
	sokoban::level level4;
	std::string s(
		"^.6.`.\n"
		"   ..@");
	std::string s2(
		"^.6.`.\n"
		"   .@.");
	std::string s3(
		"^`^.`.\n"
		"   ..@");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s));
	BOOST_REQUIRE_NO_THROW(level3.parse(s2));
	BOOST_REQUIRE_NO_THROW(level4.parse(s3));
	BOOST_CHECK(level == level2);
	BOOST_CHECK(level != level3);
	BOOST_CHECK(level != level4);
}

BOOST_AUTO_TEST_CASE(parse_invalid_chars_throw) {
	sokoban::level level;
	std::string s(
		"^.6.`.\n"
		"v  ..@\n");
	BOOST_CHECK_THROW(level.parse(s), sokoban::level_parse_exception);
}

BOOST_AUTO_TEST_CASE(ostream_insertion) {
	sokoban::level level;
	std::string s(
		"^.6.`.\n"
		"   ..@\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	std::ostringstream os;
	os << level;
	BOOST_CHECK_EQUAL(s, os.str());
}

BOOST_AUTO_TEST_CASE(move_avatar) {
	sokoban::level level;
	std::string s(
		"^.6.`.\n"
		"   ..@\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	sokoban::level::position_type avatar_old(5, 1);
	sokoban::level::position_type avatar_new(5, 0);
	BOOST_CHECK_NO_THROW(level.move_avatar(avatar_new));
	const sokoban::level::position_type &avatar(level.avatar());
	BOOST_CHECK_EQUAL(avatar_new.first, avatar.first);
	BOOST_CHECK_EQUAL(avatar_new.second, avatar.second);
}

BOOST_AUTO_TEST_CASE(move_rock) {
	sokoban::level level;
	std::string s(
		"^.6.`.\n"
		"   ..@\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	sokoban::level::position_type rock_old(4, 0);
	sokoban::level::position_type rock_new(3, 0);
	BOOST_CHECK_NO_THROW(level.move_rock(rock_old, rock_new));
	BOOST_CHECK(level.rocks().end() != level.rocks().find(rock_new));
	BOOST_CHECK(level.rocks().end() == level.rocks().find(rock_old));
}

BOOST_AUTO_TEST_SUITE_END()
