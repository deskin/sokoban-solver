#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

#include "analyze.h"
#include "errors.h"
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

BOOST_AUTO_TEST_CASE(run_basic) {
	std::string s("6@.\n");
	sokoban::simulator sim(s);
	BOOST_REQUIRE_NO_THROW(sim.run());
	BOOST_CHECK(sim.win());
	BOOST_CHECK(sokoban::is_win(sim.steps().back()));
}

BOOST_AUTO_TEST_CASE(win_before_run_throws) {
	std::string s("6@.\n");
	sokoban::simulator sim(s);
	BOOST_CHECK_THROW(sim.win(), sokoban::simulator_not_run);
}

BOOST_AUTO_TEST_CASE(win_fails_impossible_level) {
	std::string s("^@`\n");
	sokoban::simulator sim(s);
	BOOST_REQUIRE_NO_THROW(sim.run());
	BOOST_CHECK(!sim.win());
}

BOOST_AUTO_TEST_SUITE_END()
