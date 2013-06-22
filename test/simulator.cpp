#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "simulator.h"

BOOST_AUTO_TEST_SUITE(simulator)

BOOST_AUTO_TEST_CASE(construct) {
	std::string s("6@.\n");
	BOOST_CHECK_NO_THROW(sokoban::simulator sim(s));
}

BOOST_AUTO_TEST_CASE(get_steps) {
	std::string s("6@.\n");
	sokoban::simulator sim(s);
	BOOST_CHECK_NO_THROW(sim.steps());
}

BOOST_AUTO_TEST_SUITE_END()
