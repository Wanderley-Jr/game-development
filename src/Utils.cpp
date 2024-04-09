#include "Utils.h"
#include "Direction.h"

namespace Game {
namespace Utils {

void toDirectionVector(Vector& direction) {
	if (direction.x > 0) {
		direction.x = 1;
	} else if (direction.x < 0) {
		direction.x = -1;
	} else {
		direction.x = 0;
	}

	if (direction.y > 0) {
		direction.y = 1;
	} else if (direction.y < 0) {
		direction.y = -1;
	} else {
		direction.y = 0;
	}
}

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