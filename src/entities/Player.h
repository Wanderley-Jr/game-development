#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "entities/GameObject.h"
#include "graphics/Animation.h"

namespace Game {

class Player : public Object {
   protected:
	const Atlas& atlas;
	Direction direction;
	float attackDuration;

	int animationIndex;
	Animation animations[3];

	void loadAnimations();
	void switchAnimation(int animation);

   public:
	Player(const Atlas& atlas, const float x, const float y);

	void onDirectionUpdate(const Events::UpdateDirection::Type& event);
	void onAttack(const Events::Attack::Type& event);

	void render(SDL_Renderer* renderer, const float dt, const int x, const int y) override;
	void physics(const float dt) override;
};
}  // namespace Game

#endif