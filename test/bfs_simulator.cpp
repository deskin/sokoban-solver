#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

#include "analyze.h"
#include "bfs_simulator.h"
#include "errors.h"

BOOST_AUTO_TEST_SUITE(bfs_simulator)

BOOST_AUTO_TEST_CASE(construct) {
	std::string s("6@.\n");
	BOOST_CHECK_NO_THROW(sokoban::bfs_simulator sim(s));
}

BOOST_AUTO_TEST_CASE(get_steps) {
	std::string s("6@.\n");
	sokoban::bfs_simulator sim(s);
	BOOST_CHECK_NO_THROW(sim.steps());
}

BOOST_AUTO_TEST_CASE(run_basic) {
	std::string s("6@.\n");
	sokoban::bfs_simulator sim(s);
	BOOST_REQUIRE_NO_THROW(sim.run());
	BOOST_CHECK(sim.win());
	BOOST_CHECK(sokoban::is_win(sim.steps().back()));
}

BOOST_AUTO_TEST_CASE(win_before_run_throws) {
	std::string s("6@.\n");
	sokoban::bfs_simulator sim(s);
	BOOST_CHECK_THROW(sim.win(), sokoban::simulator_not_run);
}

BOOST_AUTO_TEST_CASE(win_fails_impossible_level) {
	std::string s("^@`\n");
	sokoban::bfs_simulator sim(s);
	BOOST_REQUIRE_NO_THROW(sim.run());
	BOOST_CHECK(!sim.win());
}

BOOST_AUTO_TEST_CASE(run_step_1) {
	std::string s("^`@\n");
	sokoban::bfs_simulator sim(s);
	BOOST_REQUIRE_NO_THROW(sim.run());
	BOOST_CHECK(sim.win());
	const sokoban::bfs_simulator::steps_type &steps(sim.steps());
	BOOST_CHECK_EQUAL(2, steps.size());
}

BOOST_AUTO_TEST_SUITE_END()
