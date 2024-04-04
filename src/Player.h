#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <deque>
#include "GameObject.h"
#include "PlayerSprite.h"

namespace Game {
class Player : public Object {
   protected:
	Uint8 directions;
	std::deque<Direction> directionOrder;
	PlayerSprite sprite;
	float attackDuration;

   public:
	Player(PlayerSprite sprite, const float x, const float y);

	void onDirectionUpdate(const Events::UpdateDirection::Type& event);
	void onAttack(const Events::Attack::Type& event);

	void render(SDL_Renderer* renderer, const float dt, int tileSize) override;
	void physics(const float dt) override;
};
}  // namespace Game

#endif