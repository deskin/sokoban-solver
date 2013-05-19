//#define BOOST_TEST_MODULE basic test 2
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(tautology_test_2) {
	BOOST_CHECK_EQUAL(0, 0);
}
