#include <SDL.h>

#include "Player.h"
#include "Utils.h"

namespace Game {

void Player::render(SDL_Renderer* renderer, int tileSize) {
	sprite.render(renderer, (int)(position.x * tileSize), (int)(position.y * tileSize));
}

Player::Player(Sprite sprite, float x, const float y) : Object(x, y), sprite(sprite) {
	// Subscribe to keyboard events
	auto callback = Mylib::Trigger::make_callback_object<Events::UpdateDirection::Type>(*this, &Player::onDirectionUpdate);
	Events::playerMove.subscribe(callback);
}

void Player::physics(const float dt) {
	Object::physics(dt);
}

void Player::onDirectionUpdate(const Events::UpdateDirection::Type& event) {
	// Update directions
	if (event.start) {
		directions |= 1 << (int)event.direction;
	} else {
		directions &= ~(1 << (int)event.direction);
	}

	printf("Received: %d\n", (int)event.direction);
	printf("Directions: %d\n", (int)directions);

	// Update speed to properly reflect the direction
	Vector result = Vector(0, 0);
	for (int i = 0; i < 4; i++) {
		if (directions & (1 << i)) {
			result += Utils::getDirectionVector((Direction)i);
		}
	}
	if (result.length() != 0) {
		result.normalize();
	}
	speed = result * 3.5f;
}

}  // namespace Game