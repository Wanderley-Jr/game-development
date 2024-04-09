#include <SDL.h>

#include "Player.h"
#include "Utils.h"

namespace Game {

void Player::loadAnimations() {
	SDL_Rect PLAYER_STANDING({.x = 0, .y = 0, .w = 16, .h = 24});
	SDL_Rect PLAYER_WALKING_1({.x = 0, .y = 24, .w = 16, .h = 24});
	SDL_Rect PLAYER_WALKING_2({.x = 0, .y = 48, .w = 16, .h = 24});
	SDL_Rect PLAYER_ATTACKING_1({.x = 0, .y = 72, .w = 32, .h = 32});
	SDL_Rect PLAYER_ATTACKING_2({.x = 0, .y = 104, .w = 32, .h = 32});

	// Add an animation for each direction
	for (int i = 0; i < 4; i++) {
		animations[0].addAnimation({
		    {{PLAYER_STANDING, 0, 8}, -1},
		});

		animations[1].addAnimation({
		    {{PLAYER_STANDING, 0, 8}, 0.125f},
		    {{PLAYER_WALKING_1, 0, 8}, 0.125f},
		    {{PLAYER_STANDING, 0, 8}, 0.125f},
		    {{PLAYER_WALKING_2, 0, 8}, 0.125f},
		});

		animations[2].addAnimation({
		    {{PLAYER_ATTACKING_1, 8, 11}, 0.125f},
		    {{PLAYER_ATTACKING_2, 8, 11}, 0.500f},
		});

		PLAYER_STANDING.x += PLAYER_STANDING.w;
		PLAYER_WALKING_1.x += PLAYER_WALKING_1.w;
		PLAYER_WALKING_2.x += PLAYER_WALKING_2.w;
		PLAYER_ATTACKING_1.x += PLAYER_ATTACKING_1.w;
		PLAYER_ATTACKING_2.x += PLAYER_ATTACKING_2.w;
	}
}

Player::Player(const Atlas& atlas, const float x, const float y) : Object(x, y), atlas(atlas), animationIndex(0), attackDuration(-1) {
	// Subscribe to events
	auto callback1 = Mylib::Trigger::make_callback_object<Events::UpdateDirection::Type>(*this, &Player::onDirectionUpdate);
	Events::playerMove.subscribe(callback1);
	auto callback2 = Mylib::Trigger::make_callback_object<Events::Attack::Type>(*this, &Player::onAttack);
	Events::playerAttack.subscribe(callback2);

	loadAnimations();
}

void Player::render(SDL_Renderer* renderer, const float dt, const int x, const int y) {
	int oldIndex = animationIndex;
	if (attackDuration != -1) {
		animationIndex = 2;  // Attacking
	} else if (speed.x != 0 || speed.y != 0) {
		animationIndex = 1;  // Walking
	} else {
		animationIndex = 0;  // Standing
	}

	Animation& animation = animations[animationIndex];

	if (animationIndex != oldIndex) {
		animation.reset();
	}

	if (attackDuration == -1) {
		animation.setAnimation((int)direction);
	}

	animation.update(dt);
	animation.getCurrentSprite().render(atlas, x, y);
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

	printf("Speed: %f %f\n", speed.x, speed.y);

	Object::physics(dt);
}

void Player::updateSpeed() {
	// speed.set_zero();
	// for (int i = 0; i < 4; i++) {
	// 	if (directions & (1 << i)) {
	// 		speed += Utils::getDirectionVector((Direction)i);
	// 	}
	// }
	// if (speed.length() != 0) {
	// 	speed.normalize();
	// }
	// speed *= 3.5f;
}

void Player::onDirectionUpdate(const Events::UpdateDirection::Type& event) {
	// Log everything
	printf("Player::onDirectionUpdate: start=%d, direction=%d\n", event.start, event.direction);
	printf("Player::onDirectionUpdate: speed=%f %f\n", speed.x, speed.y);
	printf("Player::onDirectionUpdate: direction=%d\n", direction);

	if (event.start) {
		// If player is already moving in that direction, don't do anything
		if ((event.direction == Direction::DOWN && speed.y > 0) ||
		    (event.direction == Direction::UP && speed.y < 0) ||
		    (event.direction == Direction::LEFT && speed.x < 0) ||
		    (event.direction == Direction::RIGHT && speed.x > 0)) {
			return;
		}

		// Calculate new speed
		Vector currentSpeed = speed;
		Vector newSpeed = Utils::getDirectionVector(event.direction);
		Utils::toDirectionVector(currentSpeed);
		speed = currentSpeed + newSpeed;

		// Normalize the speed vector to make movement equal on all directions
		if (speed.x != 0 || speed.y != 0) {
			speed.normalize();
			speed *= 3.5f;
		}

		// Update direction
		direction = event.direction;
	} else {
		// When player stops moving in a direction, reset his speed (only on that axis)
		if (event.direction == Direction::UP || event.direction == Direction::DOWN) {
			speed.y = 0;
		} else {
			speed.x = 0;
		}

		// If only one direction is active, adjust the speed to maintain the total speed
		if ((speed.x != 0 && speed.y == 0) || (speed.x == 0 && speed.y != 0)) {
			speed.normalize();
			speed *= 3.5f;
		}

		// Set the direction to his previous direction, which must be
		// the direction he is moving to, according to his speed.
		if (speed.x != 0) {
			direction = speed.x > 0 ? Direction::RIGHT : Direction::LEFT;
		} else if (speed.y != 0) {
			direction = speed.y > 0 ? Direction::DOWN : Direction::UP;
		}
	}

	printf("After\nPlayer::onDirectionUpdate: start=%d, direction=%d\n", event.start, event.direction);
	printf("Player::onDirectionUpdate: speed=%f %f\n", speed.x, speed.y);
	printf("Player::onDirectionUpdate: direction=%d\n", direction);
}

void Player::onAttack(const Events::Attack::Type& event) {
	if (attackDuration != -1) return;
	attackDuration = 0;
	animations[2].setAnimation((int)direction);
}

}  // namespace Game