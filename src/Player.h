#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "GameObject.h"

namespace Game {
class Player : public Object {
   protected:
	Uint8 directions;
	Sprite sprite;

   public:
	Player(Sprite sprite, const float x, const float y);

	void onDirectionUpdate(const Events::UpdateDirectionEvent& event);

	void render(SDL_Renderer* renderer, int tileSize) override;
	void physics(const float dt) override;
};
}  // namespace Game

#endif