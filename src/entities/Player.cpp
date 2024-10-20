#include <SDL2/SDL.h>

#include "entities/Player.h"
#include "entities/Enemy.h"
#include "Utils.h"

namespace Game {

Player::Player(const Atlas& atlas, const World* world) : Character("player", world), atlas(atlas), attackDuration(-1) {
	this->health = 100;

	// Subscribe to events
	auto callback1 = Mylib::Trigger::make_callback_object<Events::UpdateDirection::Type>(*this, &Player::onDirectionUpdate);
	Events::playerMove.subscribe(callback1);
	auto callback2 = Mylib::Trigger::make_callback_object<Events::Attack::Type>(*this, &Player::onAttack);
	Events::playerAttack.subscribe(callback2);
	auto callback3 = Mylib::Trigger::make_callback_object<Events::Dash::Type>(*this, &Player::onDash);
	Events::playerDash.subscribe(callback3);

	// Create hitboxes
	colliders.push_back(Collider("player_hitbox", *this, Vector::zero(), Vector(1, 1), false, true, [](Collider& other) {
		if (other.getOwner().getName() == "player") return;
	}));

	colliders.push_back(Collider("player_sword", *this, Vector::zero(), Vector::zero(), true, false, [this, world](Collider& other) {
		auto enemy = dynamic_cast<Enemy*>(&other.getOwner());

		if (other.getName() != "enemy_hitbox" || enemy == nullptr || enemy->getInvincibleDuration() > 0) return;

		enemy->setHealth(std::max(enemy->getHealth() - 20, 0));
		enemy->setInvincibleDuration(0.5f);

		enemy->setSpeed(Utils::toDirectionVector(direction) * 5.0f);
		enemy->setForcedMovementDuration(0.25f);

		Mix_PlayChannel(4, this->swordHitSound, 0);

		if (enemy->getHealth() == 0) {
			// Kill enemy
			// auto& objs = world->getObjects();
			// objs.erase(std::remove(objs.begin(), objs.end(), enemy), objs.end());
			this->score++;
		}
	}));

	// Set up animations
	animation.addAnimation(Sprites::PLAYER_STANDING, {0.125f});

	animation.addAnimation({{Sprites::PLAYER_WALKING_1, 0.15f},
	                        {Sprites::PLAYER_STANDING, 0.15f},
	                        {Sprites::PLAYER_WALKING_2, 0.15f},
	                        {Sprites::PLAYER_STANDING, 0.15f}});

	animation.addAnimation(Sprites::PLAYER_ATTACKING, {0.2f, 0.4f});

	// Set up sounds
	this->swordSwingSound = Mix_LoadWAV("./assets/sword_swing.wav");
	this->swordHitSound = Mix_LoadWAV("./assets/sword_hit.wav");
	this->dashSound = Mix_LoadWAV("./assets/dash.wav");
}

void Player::render(const Atlas& atlas, const float dt, const int x, const int y) {
	if (attackDuration != -1) {
		animation.setAnimation(2);  // Attacking
	} else if (speed.x != 0 || speed.y != 0) {
		animation.setAnimation(1);  // Walking
	} else {
		animation.setAnimation(0);  // Standing
	}

	if (attackDuration == -1) {
		animation.setDirection((int)direction);
	}

	animation.update(dt);

	SDL_Color color = {255, 255, 255, 255};

	if (invincibleDuration > 0) {
		if ((int)(invincibleDuration / 0.10f) % 2 == 0) {
			color.a = 63;
		}
	} else if (forcedMovementDuration > 0) {
		color.a = 63;
	}

	// atlas.render("Hero", x, y);
	atlas.render(animation.getCurrentSprite(), x, y, color);
}

void Player::update(const float dt) {
	// Prevent movement while player is attacking
	if (attackDuration != -1) {
		attackDuration += dt;
		if (attackDuration >= 0.375f) {
			attackDuration = -1;
			colliders[1].setActive(false);
		}
		return;
	}

	Character::update(dt);
}

void Player::onDirectionUpdate(const Events::UpdateDirection::Type& event) {
	Vector currentSpeed = Utils::toDirectionVector(speed);
	Vector newSpeed = Utils::toDirectionVector(event.direction);

	if (forcedMovementDuration > 0) {
		return;
	}

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
	if (attackDuration != -1 || forcedMovementDuration > 0) return;

	// Play sound effect
	Mix_PlayChannel(4, swordSwingSound, 0);

	attackDuration = 0;

	float x = 0, y = 0, w, h;  // The dimensions of the collider

	switch (direction) {
	case Direction::LEFT:
	case Direction::RIGHT:
		w = 6.0f / 16;
		h = 1;

		x = direction == Direction::LEFT ? -w : 1;
		break;
	case Direction::UP:
	case Direction::DOWN:
		w = 1;
		h = 6.0f / 16;

		y = direction == Direction::UP ? -h : 1;
		break;
	}

	// Enable sword collider
	colliders[1].setPosition(Vector(x, y));
	colliders[1].setSize(Vector(w, h));
	colliders[1].setActive(true);
}

void Player::onDash(const Events::Dash::Type& event) {
	if (forcedMovementDuration > 0) return;
	setSpeed(Utils::toDirectionVector(direction) * 15.0f);
	setForcedMovementDuration(0.25f);
	Mix_PlayChannel(3, dashSound, 0);
}

}  // namespace Game