#define BOOST_TEST_MODULE sokoban tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <string>
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

BOOST_AUTO_TEST_CASE(parse_get_avatar) {
	sokoban::level level;
	std::string s("@`^\n"
		      ".`^");
	BOOST_CHECK_NO_THROW(level.parse(s));
	const std::pair<size_t, size_t> &pos(
		level.avatar());
	BOOST_CHECK_EQUAL(pos.first, 0);
	BOOST_CHECK_EQUAL(pos.second, 0);
}

BOOST_AUTO_TEST_SUITE_END()
