#include "entities/GameObject.h"
#include "Events.h"
#include "Utils.h"

namespace Game {

void Object::update(const float dt) {
	position += speed * dt;
}

}  // namespace Game