#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "tile.h"

BOOST_AUTO_TEST_SUITE(tile)

BOOST_AUTO_TEST_CASE(construct) {
	BOOST_CHECK_NO_THROW(sokoban::tile{sokoban::tile::kind::invalid});
	BOOST_CHECK_NO_THROW(sokoban::tile{sokoban::tile::kind::valid});
}

BOOST_AUTO_TEST_SUITE_END()
