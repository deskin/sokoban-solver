#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "tuple-hack.h"

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
			sokoban::level::tile::pointer_type()),
		sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(t.unset_pit(), sokoban::tile_invalid_exception);
}

BOOST_AUTO_TEST_CASE(pit_get_set) {
	sokoban::level::positions_type s;
	sokoban::level::tile::pointer_type i;
	sokoban::tile t{sokoban::tile::kind::valid};
	bool pit_valid;

	s.insert(std::make_pair<size_t, size_t>(1, 0));
	BOOST_CHECK_NO_THROW(t.set_pit(s.begin()));
	BOOST_CHECK_NO_THROW(std::tie(pit_valid, i) = t.pit());
	BOOST_CHECK(pit_valid);
	BOOST_CHECK(i == s.begin());
	BOOST_CHECK_NO_THROW(t.unset_pit());
	BOOST_CHECK_NO_THROW(std::tie(pit_valid, std::ignore) = t.pit());
	BOOST_CHECK(!pit_valid);
}

BOOST_AUTO_TEST_SUITE_END()
