#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "errors.h"
#include "level.h"

namespace sokoban {

typedef level::tile tile;

} // namespace sokoban

BOOST_AUTO_TEST_SUITE(tile)

BOOST_AUTO_TEST_CASE(construct) {
	BOOST_CHECK_NO_THROW(sokoban::tile{sokoban::tile::kind::invalid});
	BOOST_CHECK_NO_THROW(sokoban::tile{sokoban::tile::kind::valid});
}

BOOST_AUTO_TEST_CASE(invalid_pit_get_set) {
	sokoban::tile t{sokoban::tile::kind::invalid};
	BOOST_CHECK_THROW(t.pit(), sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(
		t.set_pit(
			sokoban::level::positions_type::iterator()),
		sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(t.unset_pit(), sokoban::tile_invalid_exception);
}

BOOST_AUTO_TEST_CASE(pit_get_set) {
	sokoban::level::positions_type s;
	s.insert(std::make_pair<size_t, size_t>(1, 0));
	sokoban::tile t{sokoban::tile::kind::valid};
	BOOST_CHECK_NO_THROW(t.set_pit(s.begin()));
	sokoban::level::positions_type::iterator p;
	BOOST_CHECK_NO_THROW(p = t.pit());
	BOOST_CHECK(p == s.begin());
	BOOST_CHECK_NO_THROW(t.unset_pit());
	BOOST_CHECK(p != s.begin());
}

BOOST_AUTO_TEST_SUITE_END()
