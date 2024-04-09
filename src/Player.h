#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <deque>

#include "GameObject.h"
#include "PlayerSprite.h"
#include "Animation.h"
#include "Sprite.h"

namespace Game {

// namespace PlayerSprites {
// const Sprite PLAYER_STANDING({.x = 0, .y = 0, .w = 16, .h = 24});
// const Sprite PLAYER_WALKING_1({.x = 0, .y = 24, .w = 16, .h = 24});
// const Sprite PLAYER_WALKING_2({.x = 0, .y = 48, .w = 16, .h = 24});
// const Sprite PLAYER_ATTACKING_1({.x = 0, .y = 72, .w = 32, .h = 32});
// const Sprite PLAYER_ATTACKING_2({.x = 0, .y = 104, .w = 32, .h = 32});
// }  // namespace PlayerSprites

class Player : public Object {
   protected:
	const Atlas& atlas;
	Uint8 directions;
	std::deque<Direction> directionOrder;
	float attackDuration;

	int animationIndex;
	Animation animations[3];

	void updateSpeed();
	void loadAnimations();

   public:
	Player(const Atlas& atlas, const float x, const float y);

	void onDirectionUpdate(const Events::UpdateDirection::Type& event);
	void onAttack(const Events::Attack::Type& event);

	void render(SDL_Renderer* renderer, const float dt, const int x, const int y) override;
	void physics(const float dt) override;
};
}  // namespace Game

#endif