#include <SDL.h>

#include "Player.h"
#include "Utils.h"

namespace Game {

// Adds the animation for each direction
void addAnimation(Animation& animation, std::vector<AnimationFrame> frames) {
	for (int i = 0; i < 4; i++) {
		animation.addAnimation(frames);

		// Translate each sprite to the right. Since in the atlas
		// the sprites are ordered according to their direction, we
		// can just add the width of the sprite to get the next one.
		for (auto& frame : frames) {
			frame.sprite.x += frame.sprite.width;
		}
	}
}

void Player::loadAnimations() {
	addAnimation(
	    animations[0],
	    {
	        {Sprites::PLAYER_STANDING, 0.125f},
	    });

	addAnimation(
	    animations[1],
	    {
	        {Sprites::PLAYER_STANDING, 0.125f},
	        {Sprites::PLAYER_WALKING_1, 0.125f},
	        {Sprites::PLAYER_STANDING, 0.125f},
	        {Sprites::PLAYER_WALKING_2, 0.125f},
	    });

	addAnimation(
	    animations[2],
	    {
	        {Sprites::PLAYER_ATTACKING_1, 0.125f},
	        {Sprites::PLAYER_ATTACKING_2, 0.500f},
	    });
}

void Player::switchAnimation(int animation) {
	if (animationIndex == animation) return;
	animations[animation].reset();
	animations[animation].setAnimation((int)direction);
	animationIndex = animation;
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
	if (attackDuration != -1) {
		switchAnimation(2);  // Attacking
	} else if (speed.x != 0 || speed.y != 0) {
		switchAnimation(1);  // Walking
	} else {
		switchAnimation(0);  // Standing
	}

	Animation& animation = animations[animationIndex];

	if (attackDuration == -1) {
		animation.setAnimation((int)direction);
	}

	animation.update(dt);
	atlas.render(animation.getCurrentSprite(), x, y);
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

void Player::onDirectionUpdate(const Events::UpdateDirection::Type& event) {
	Vector currentSpeed = Utils::toDirectionVector(speed);
	Vector newSpeed = Utils::toDirectionVector(event.direction);

	if (event.start) {
		// If player is already moving in that direction, don't do anything
		if ((newSpeed.x && newSpeed.x == currentSpeed.x) || (newSpeed.y && newSpeed.y == currentSpeed.y)) {
			return;
		}

		// Otherwise, increase speed and change direction
		speed = currentSpeed + newSpeed;
		direction = event.direction;
	} else {
		// Nullify movement in the same axis of the direction
		if (newSpeed.x) {
			currentSpeed.x = 0;
		} else if (newSpeed.y) {
			currentSpeed.y = 0;
		}
		speed = currentSpeed;

		// Set direction to previous one, which must be the direction
		// the player is moving in, according to his speed.
		if (speed.x > 0) {
			direction = Direction::RIGHT;
		} else if (speed.x < 0) {
			direction = Direction::LEFT;
		} else if (speed.y > 0) {
			direction = Direction::DOWN;
		} else if (speed.y < 0) {
			direction = Direction::UP;
		}
	}

	// Normalize the speed vector to make movement equal on all directions
	if (speed.x != 0 || speed.y != 0) {
		speed.normalize();
		speed *= 3.5f;
	}
}

void Player::onAttack(const Events::Attack::Type& event) {
	if (attackDuration != -1) return;
	attackDuration = 0;
}

}  // namespace Game