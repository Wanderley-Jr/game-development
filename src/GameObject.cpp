#include "GameObject.h"

#include "Events.h"
#include "Utils.h"

namespace Game {

Object::Object(const float x, const float y) {
	this->position = Vector(x, y);
	this->speed = Vector::zero();
}

void Object::physics(const float dt) {
	if (!speed.x && !speed.y) return;

	position += speed * dt;

	// print all info
	// std::cout << "position: " << position.x << ", " << position.y << std::endl;
	// std::cout << "speed: " << speed.x << ", " << speed.y << std::endl;

	// After done moving an entire tile, update the real position
	// if (translate.length() >= 1) {
	// 	position += Utils::getDirectionVector(direction);
	// 	translate.set_zero();
	// 	speed.set_zero();
	// }
}

}  // namespace Game