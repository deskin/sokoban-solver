#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "level.h"
#include "level_mover.h"

BOOST_AUTO_TEST_SUITE(level_mover)

BOOST_AUTO_TEST_CASE(size) {
	sokoban::level level;
	sokoban::level level2;
	std::string s("^`@\n");
	std::string s2(
		"^`@\n"
		" ..\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	BOOST_REQUIRE_NO_THROW(level2.parse(s2));
	BOOST_CHECK_EQUAL(1, sokoban::level_mover(level).size());
	BOOST_CHECK_EQUAL(2, sokoban::level_mover(level2).size());
}

BOOST_AUTO_TEST_SUITE_END()
