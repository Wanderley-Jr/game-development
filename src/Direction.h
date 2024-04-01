#ifndef DIRECTION_H
#define DIRECTION_H

#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

enum class Direction {
	DOWN,
	UP,
	LEFT,
	RIGHT,
	NONE
};

}  // namespace Game

#endif