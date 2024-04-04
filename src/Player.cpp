#include <SDL.h>

#include "Player.h"
#include "Utils.h"

namespace Game {

Player::Player(PlayerSprite sprite, float x, const float y) : Object(x, y), sprite(sprite), directions(0), attackDuration(-1) {
	// Subscribe to keyboard events
	auto callback1 = Mylib::Trigger::make_callback_object<Events::UpdateDirection::Type>(*this, &Player::onDirectionUpdate);
	Events::playerMove.subscribe(callback1);

	// Subscribe to attack events
	auto callback2 = Mylib::Trigger::make_callback_object<Events::Attack::Type>(*this, &Player::onAttack);
	Events::playerAttack.subscribe(callback2);
}

void Player::render(SDL_Renderer* renderer, const float dt, int tileSize) {
	sprite.update(dt);
	sprite.render(renderer, (int)(position.x * tileSize), (int)(position.y * tileSize));
}

void Player::physics(const float dt) {
	if (attackDuration != -1) {
		attackDuration += dt;
		if (attackDuration > 0.5f) {
			sprite.setState(PlayerSprite::STANDING);
			attackDuration = -1;
		}
		return;
	}

	Object::physics(dt);
}

void Player::onDirectionUpdate(const Events::UpdateDirection::Type& event) {
	if (attackDuration != -1) return;

	if (event.start && directionOrder.size() && directionOrder.back() == event.direction) {
		return;
	}

	// Update directions
	if (event.start) {
		directions |= 1 << (int)event.direction;
		directionOrder.push_back(event.direction);
	} else {
		directions &= ~(1 << (int)event.direction);
		directionOrder.erase(std::remove(directionOrder.begin(), directionOrder.end(), event.direction), directionOrder.end());
	}
	if (!directionOrder.empty()) {
		sprite.setDirection(directionOrder.back());
	}

	// Update speed to properly reflect the direction
	speed.set_zero();
	for (int i = 0; i < 4; i++) {
		if (directions & (1 << i)) {
			speed += Utils::getDirectionVector((Direction)i);
		}
	}
	if (speed.length() != 0) {
		speed.normalize();
	}
	speed *= 3.5f;

	// If player started moving, start the animation
	if (event.start && directionOrder.size() == 1) {
		sprite.setState(PlayerSprite::WALKING);
	}
	// Otherwise, stop the animation
	if (directionOrder.empty()) {
		sprite.setState(PlayerSprite::STANDING);
	}
}

void Player::onAttack(const Events::Attack::Type& event) {
	if (attackDuration != -1) return;

	directions = 0;
	directionOrder.clear();
	speed.set_zero();

	// For now, we only play the attack animation
	sprite.setState(PlayerSprite::ATTACKING);
	attackDuration = 0;
}

}  // namespace Game