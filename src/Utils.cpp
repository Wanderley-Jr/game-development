#include "Utils.h"
#include "Direction.h"

namespace Game {
namespace Utils {

// Returns a normalized vector representing a certain direction
Vector getDirectionVector(Direction direction) {
	switch (direction) {
	case Direction::UP:
		return Vector(0, -1);
	case Direction::DOWN:
		return Vector(0, 1);
	case Direction::LEFT:
		return Vector(-1, 0);
	case Direction::RIGHT:
		return Vector(1, 0);
	}
	return Vector(0, 0);
}

}  // namespace Utils
}  // namespace Game