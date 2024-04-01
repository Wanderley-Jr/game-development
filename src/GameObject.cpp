#include "GameObject.h"

#include "Events.h"
#include "Utils.h"

namespace Game {

Vector Object::getPosition() {
	return position + translate;
}

Vector Object::getSpeed() {
	return speed;
}

Direction Object::getDirection() {
	return direction;
}

void Object::setPosition(const Vector position) {
	this->position = position;
}

void Object::setSpeed(const Vector speed) {
	this->speed = speed;
}

void Object::setDirection(Direction direction) {
	this->direction = direction;
}

Object::Object(const float x, const float y) {
	this->position = Vector(x, y);
	this->speed = Vector::zero();
	this->translate = Vector::zero();
	this->direction = Direction::NONE;
}

void Object::physics(const float dt) {
	// printf position and translate etc
	// printf("Position: %f, %f\n", position.x, position.y);
	// printf("Translate: %f, %f\n", translate.x, translate.y);
	// printf("Speed: %f, %f\n", speed.x, speed.y);
	// printf("Direction: %d\n", direction);

	if (!speed.x && !speed.y) return;

	translate += speed * dt;

	// After done moving an entire tile, update the real position
	if (translate.length() >= 1) {
		position += Utils::getDirectionVector(direction);
		translate.set_zero();
		speed.set_zero();
	}
}

}  // namespace Game