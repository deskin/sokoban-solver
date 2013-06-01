#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <sstream>
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

BOOST_AUTO_TEST_CASE(is_valid) {
	BOOST_CHECK(!sokoban::tile{sokoban::tile::kind::invalid}.is_valid());
	BOOST_CHECK(sokoban::tile{sokoban::tile::kind::valid}.is_valid());

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

BOOST_AUTO_TEST_CASE(invalid_rock_get_set) {
	sokoban::tile t{sokoban::tile::kind::invalid};
	BOOST_CHECK_THROW(t.rock(), sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(
		t.set_rock(
			sokoban::level::tile::pointer_type()),
		sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(t.unset_rock(), sokoban::tile_invalid_exception);
}

BOOST_AUTO_TEST_CASE(rock_get_set) {
	sokoban::level::positions_type s;
	sokoban::level::tile::pointer_type i;
	sokoban::tile t{sokoban::tile::kind::valid};
	bool rock_valid;

	s.insert(std::make_pair<size_t, size_t>(1, 0));
	BOOST_CHECK_NO_THROW(t.set_rock(s.begin()));
	BOOST_CHECK_NO_THROW(std::tie(rock_valid, i) = t.rock());
	BOOST_CHECK(rock_valid);
	BOOST_CHECK(i == s.begin());
	BOOST_CHECK_NO_THROW(t.unset_rock());
	BOOST_CHECK_NO_THROW(std::tie(rock_valid, std::ignore) = t.rock());
	BOOST_CHECK(!rock_valid);
}

BOOST_AUTO_TEST_CASE(invalid_avatar_get_set) {
	sokoban::tile t{sokoban::tile::kind::invalid};
	BOOST_CHECK_THROW(t.avatar(), sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(
		t.set_avatar(),
		sokoban::tile_invalid_exception);
	BOOST_CHECK_THROW(t.unset_avatar(), sokoban::tile_invalid_exception);
}

BOOST_AUTO_TEST_CASE(avatar_get_set) {
	sokoban::tile t{sokoban::tile::kind::valid};

	BOOST_CHECK_NO_THROW(t.set_avatar());
	BOOST_CHECK(t.avatar());
	BOOST_CHECK_NO_THROW(t.unset_avatar());
	BOOST_CHECK(!t.avatar());
}

BOOST_AUTO_TEST_CASE(ostream_insertion) {
	sokoban::tile t_space{sokoban::tile::kind::invalid};
	sokoban::tile t_dot{sokoban::tile::kind::valid};
	sokoban::tile t_at{sokoban::tile::kind::valid};
	sokoban::tile t_hat{sokoban::tile::kind::valid};
	sokoban::tile t_backtick{sokoban::tile::kind::valid};
	sokoban::tile t_6{sokoban::tile::kind::valid};
	sokoban::tile t_7{sokoban::tile::kind::valid};
	sokoban::level::positions_type s;

	t_at.set_avatar();

	t_hat.set_pit(s.begin());

	t_backtick.set_rock(s.begin());

	t_6.set_pit(s.begin());
	t_6.set_rock(s.begin());

	t_7.set_pit(s.begin());
	t_7.set_avatar();

	{
		std::ostringstream os;
		os << t_space;
		BOOST_CHECK_EQUAL(" ", os.str());
	}

	{
		std::ostringstream os;
		os << t_dot;
		BOOST_CHECK_EQUAL(".", os.str());
	}

	{
		std::ostringstream os;
		os << t_at;
		BOOST_CHECK_EQUAL("@", os.str());
	}

	{
		std::ostringstream os;
		os << t_hat;
		BOOST_CHECK_EQUAL("^", os.str());
	}

	{
		std::ostringstream os;
		os << t_backtick;
		BOOST_CHECK_EQUAL("`", os.str());
	}

	{
		std::ostringstream os;
		os << t_6;
		BOOST_CHECK_EQUAL("6", os.str());
	}

	{
		std::ostringstream os;
		os << t_7;
		BOOST_CHECK_EQUAL("7", os.str());
	}
}

BOOST_AUTO_TEST_SUITE_END()
