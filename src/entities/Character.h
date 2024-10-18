#include "World.h"
#include "entities/GameObject.h"

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

namespace Game {

class World;

class Character : public Object {
   protected:
	const World* world;
	Direction direction = Direction::DOWN;
	float invincibleDuration = 0;

	// Used to force the character to move in a direction for a certain amount of time.
	// When the time is elapsed, the character will stop moving. This is used for knockback and dashing.
	float forcedMovementDuration = 0;
	int health = -1;

   public:
	const World* getWorld() { return world; }

	float getInvincibleDuration() const { return invincibleDuration; }
	void setInvincibleDuration(const float invincibleDuration) { this->invincibleDuration = invincibleDuration; }

	float getForcedMovementDuration() const { return forcedMovementDuration; }
	void setForcedMovementDuration(const float forcedMovementDuration) { this->forcedMovementDuration = forcedMovementDuration; }

	int getHealth() const { return health; }
	void setHealth(const int health) { this->health = health; }

	Character(const string name, const World* world) : Object(std::move(name)), world(world) {}

	void update(const float dt) override;
	virtual void ai(const float dt) = 0;
};

}  // namespace Game

#endif