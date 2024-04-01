#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "GameObject.h"

namespace Game {
class Player : public Object {
   protected:
	Sprite sprite;

   public:
	Player(Sprite sprite, const float x, const float y);

	void onKeyPress(const Events::Keyboard::Type& key);
	void render(SDL_Renderer* renderer, int tileSize) override;
};
}  // namespace Game

#endif