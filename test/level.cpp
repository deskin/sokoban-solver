#define BOOST_TEST_MODULE sokoban tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <utility>

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
	const std::set<sokoban::level::position_type> &pits(level.pits());
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

BOOST_AUTO_TEST_SUITE_END()
