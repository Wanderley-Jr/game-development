#include <SDL.h>

#include "Player.h"
#include "Utils.h"

namespace Game {

Player::Player(const Atlas& atlas, float x, const float y) : Object(x, y), sprite(PlayerSprite(atlas)), directions(0), attackDuration(-1) {
	// Subscribe to keyboard events
	auto callback1 = Mylib::Trigger::make_callback_object<Events::UpdateDirection::Type>(*this, &Player::onDirectionUpdate);
	Events::playerMove.subscribe(callback1);

	// Subscribe to attack events
	auto callback2 = Mylib::Trigger::make_callback_object<Events::Attack::Type>(*this, &Player::onAttack);
	Events::playerAttack.subscribe(callback2);
}

void Player::render(SDL_Renderer* renderer, const float dt, const int x, const int y) {
	if (!directionOrder.empty() && attackDuration == -1) {
		sprite.setDirection(directionOrder.back());
	}

	if (attackDuration != -1) {
		sprite.setState(PlayerSprite::ATTACKING);
	} else if (directions != 0) {
		sprite.setState(PlayerSprite::WALKING);
	} else {
		sprite.setState(PlayerSprite::STANDING);
	}

	sprite.update(dt);

	sprite.render(renderer, x, y);
}

void Player::physics(const float dt) {
	// Prevent movement while player is attacking
	if (attackDuration != -1) {
		attackDuration += dt;
		if (attackDuration >= 0.375f) {
			attackDuration = -1;
		}
		return;
	}

	Object::physics(dt);
}

void Player::updateSpeed() {
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
}

void Player::onDirectionUpdate(const Events::UpdateDirection::Type& event) {
	// Check if the direction is already in the correct state
	int dirBit = 1 << (int)event.direction;
	if ((event.start && (directions & dirBit)) || (!event.start && !(directions & dirBit))) {
		return;
	}

	// Update directions
	if (event.start) {
		directions |= dirBit;
		directionOrder.push_back(event.direction);
	} else {
		directions &= ~dirBit;
		directionOrder.erase(std::remove(directionOrder.begin(), directionOrder.end(), event.direction), directionOrder.end());
	}

	updateSpeed();
}

void Player::onAttack(const Events::Attack::Type& event) {
	if (attackDuration != -1) return;
	attackDuration = 0;
}

}  // namespace Game