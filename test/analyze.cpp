#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "analyze.h"
#include "level.h"

BOOST_AUTO_TEST_SUITE(analyze)

BOOST_AUTO_TEST_CASE(win) {
	sokoban::level l_win;
	sokoban::level l_not_win;
	std::string s_win(
		"6.6@..\n"
		"   ...");
	std::string s_not_win(
		"6@^.`.\n"
		"   ...");
	BOOST_REQUIRE_NO_THROW(l_win.parse(s_win));
	BOOST_REQUIRE_NO_THROW(l_not_win.parse(s_not_win));
	BOOST_CHECK(sokoban::is_win(l_win));
	BOOST_CHECK(!sokoban::is_win(l_not_win));
}

BOOST_AUTO_TEST_SUITE_END()
