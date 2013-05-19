#define BOOST_TEST_MODULE basic test
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(tautology_test) {
	BOOST_CHECK_EQUAL(0, 0);
	BOOST_CHECK_NE(1, 0);
}
