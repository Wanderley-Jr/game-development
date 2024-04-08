#include "GameObject.h"
#include "Events.h"
#include "Utils.h"

namespace Game {

Object::Object(const float x, const float y) {
	this->position = Vector(x, y);
	this->speed = Vector::zero();
}

void Object::physics(const float dt) {
	position += speed * dt;
}

}  // namespace Game