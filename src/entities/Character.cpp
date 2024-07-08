#include "entities/Character.h"

namespace Game {

void Character::update(const float dt) {
	Object::update(dt);

	invincibleDuration = std::max(invincibleDuration - dt, 0.0f);

	if (forcedMovementDuration > 0) {
		forcedMovementDuration = std::max(forcedMovementDuration - dt, 0.0f);

		if (forcedMovementDuration > 0) {
			return;
		}

		speed.set_zero();
	}

	this->ai(dt);
}

}  // namespace Game