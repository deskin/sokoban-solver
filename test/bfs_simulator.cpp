#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "bfs_simulator.h"

BOOST_AUTO_TEST_SUITE(bfs_simulator)

BOOST_AUTO_TEST_CASE(construct) {
	std::string s("6@.\n");
	BOOST_CHECK_NO_THROW(sokoban::bfs_simulator sim(s));
}

BOOST_AUTO_TEST_SUITE_END()
