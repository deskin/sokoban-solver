#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "level.h"
#include "level_mover.h"

BOOST_AUTO_TEST_SUITE(level_mover)

BOOST_AUTO_TEST_CASE(size_one) {
	sokoban::level level;
	std::string s("^`@\n");
	BOOST_REQUIRE_NO_THROW(level.parse(s));
	sokoban::level_mover mover(level);
	BOOST_CHECK_EQUAL(1, mover.size());
}

BOOST_AUTO_TEST_SUITE_END()
