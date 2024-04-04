#include <vector>
#include <SDL.h>

#include "Atlas.h"
#include "Direction.h"
#include "Animation.h"

#ifndef PLAYER_SPRITE_H
#define PLAYER_SPRITE_H

namespace Game {

class PlayerSprite {
   public:
	enum State {
		STANDING,
		WALKING,
		ATTACKING,
	};

   protected:
	const Atlas& atlas;
	State state;
	Direction direction;
	Animation animations[3];

   public:
	Direction getDirection() const {
		return direction;
	}

	void setDirection(Direction direction) {
		this->direction = direction;
	}

	State getState() const {
		return state;
	}

	void setState(State state) {
		this->state = state;
		animations[state].reset();
	}

	PlayerSprite(const Atlas& atlas);

	void render(SDL_Renderer* renderer, int x, int y);
	void update(float dt);
};
}  // namespace Game

#endif