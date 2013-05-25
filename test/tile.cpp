#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "tile.h"

BOOST_AUTO_TEST_SUITE(tile)

BOOST_AUTO_TEST_CASE(construct) {
	sokoban::tile();
}

BOOST_AUTO_TEST_SUITE_END()
