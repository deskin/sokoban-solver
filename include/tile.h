#ifndef SOKOBAN_TILE_H_
#define SOKOBAN_TILE_H_

namespace sokoban {

class tile {
public:
	enum class kind {
		invalid,
		valid
	};

	explicit tile(kind) {}
};

} // namespace sokoban

#endif // SOKOBAN_TILE_H_
