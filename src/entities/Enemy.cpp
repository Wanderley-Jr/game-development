#include "Events.h"
#include "entities/Character.h"
#include "entities/Enemy.h"
#include "entities/Player.h"

namespace Game {

Enemy::Enemy(const string name, const World* world) : Character(std::move(name), world) {
	this->health = 100;

	this->attackSound = Mix_LoadWAV("./assets/boar_charge.wav");
	this->hurtSound = Mix_LoadWAV("./assets/hurt.wav");

	colliders.push_back(Collider("enemy_hitbox", *this, Vector::zero(), Vector(1, 1), false, true, [this](Collider& other) {
		// Cast owner of other collider to player
		Player* player = dynamic_cast<Player*>(&other.getOwner());
		if (other.getName() == "player_hitbox" && player != nullptr && player->getInvincibleDuration() == 0) {
			player->setHealth(std::max(player->getHealth() - 10, 0));
			player->setInvincibleDuration(0.5f);

			player->setSpeed(speed);
			player->setForcedMovementDuration(0.2f);

			Mix_PlayChannel(6, hurtSound, 0);
		}
		aiStatus = 0;
		aiDelay = 0.5f;
		if (this->getForcedMovementDuration() == 0) {
			speed.set_zero();
		}
	}));

	// Standing animation
	animation.addAnimation(Sprites::BOAR_STANDING, {0.125f});

	// Walking animation
	animation.addAnimation(Sprites::BOAR_WALKING, {0.125f, 0.125f, 0.125f});
}

void Enemy::render(const Atlas& atlas, const float dt, const int x, const int y) {
	if (speed.length() == 0) {
		animation.setAnimation(0);
	} else {
		animation.setAnimation(1);
	}

	// Draw enemy in red color during charge animation
	SDL_Color color = {255, 255, 255, 255};
	if (aiStatus == 2) {
		color.g = color.b = 63 + 192 * (aiDelay / 0.5f);
	} else if (aiStatus == 3) {
		color.g = color.b = 63;
	} else if (invincibleDuration > 0) {
		if ((int)(invincibleDuration / 0.10f) % 2 == 0) {
			color.a = 63;
		}
	}

	animation.setDirection((int)direction);
	animation.update(dt);
	atlas.render(animation.getCurrentSprite(), x, y, color);
}

void Enemy::update(const float dt) {
	Character::update(dt);
}

void Enemy::ai(const float dt) {
	// Decrement delay timer
	if (aiDelay > 0) {
		aiDelay = std::max(aiDelay - dt, 0.0f);
		return;
	}

	Vector distance = world->getPlayer()->getPosition() - position;
	Vector direction = distance;
	direction.normalize();

	// 0 = idle
	// 1 = chasing
	// 2 = preparing to charge (animation)
	// 3 = charging
	switch (aiStatus) {
	case 0:
		// If player is within 15 tiles, chase him down
		if (distance.length() < 15) {
			aiStatus = 1;
		} else {
			speed.set_zero();
		}
		break;
	case 1:
		// If the enemy has a direct line of sight to the player, being aligned on the x or y axis, begin charge attack
		if (distance.length() <= 5 && std::min(abs(distance.x), abs(distance.y)) < 0.5f) {
			aiStatus = 2;
			aiDelay = 0.5f;
			speed.set_zero();

			// Play sound effect
			Mix_PlayChannel(5, attackSound, 0);
		} else {
			speed = direction * 3.0f;
		}
		break;
	case 2:
		// After enemy has finished charging animation, begin charging
		aiStatus = 3;
		speed = Utils::toDirectionVector(this->direction) * 10.0f;
		break;
	case 3:
		// When enemy gets too far away from player, stop charging
		if (distance.length() > 5) {
			aiStatus = 0;
		}
		break;
	}

	if (speed.length() != 0) {
		this->direction = Utils::toDirection(speed);
	}
}

}  // namespace Game