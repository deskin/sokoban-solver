#define BOOST_TEST_MODULE sokoban tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "level.h"

BOOST_AUTO_TEST_SUITE(level)

BOOST_AUTO_TEST_CASE(construct) {
	sokoban::level();
}

BOOST_AUTO_TEST_SUITE_END()