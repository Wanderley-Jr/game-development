#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SDL_mixer.h>

#include "entities/GameObject.h"
#include "graphics/Animation.h"
#include "entities/Collider.h"

// adding this breaks EVERYTHING
#include "entities/Character.h"

namespace Game {

class Player : public Character {
   protected:
	const Atlas& atlas;
	float attackDuration;
	int score = 0;

	Animation animation;

	Mix_Chunk* swordSwingSound;
	Mix_Chunk* swordHitSound;
	Mix_Chunk* dashSound;

   public:
	Player(const Atlas& atlas, const World* world);

	const int getScore() const {
		return score;
	}

	void setScore(const int score) {
		this->score = score;
	}

	void onDirectionUpdate(const Events::UpdateDirection::Type& event);
	void onAttack(const Events::Attack::Type& event);
	void onDash(const Events::Dash::Type& event);

	void render(const Atlas& atlas, const float dt, const int x, const int y) override;
	void update(const float dt) override;
	void ai(const float dt) override {};  // Nothing
};
}  // namespace Game

#endif