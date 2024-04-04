#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <SDL.h>

namespace Game {

namespace Sprite {
const SDL_Rect PLAYER_STANDING = {.x = 0, .y = 0, .w = 16, .h = 24};
const SDL_Rect PLAYER_WALKING_1 = {.x = 0, .y = 24, .w = 16, .h = 24};
const SDL_Rect PLAYER_WALKING_2 = {.x = 0, .y = 48, .w = 16, .h = 24};
const SDL_Rect PLAYER_ATTACKING_1 = {.x = 0, .y = 72, .w = 32, .h = 32};
const SDL_Rect PLAYER_ATTACKING_2 = {.x = 0, .y = 104, .w = 32, .h = 32};
}  // namespace Sprite

// Class responsible for managing all sprites.
class Atlas {
   private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;

   public:
	Atlas(SDL_Renderer* renderer, const char* filename);
	~Atlas();

	void render(SDL_Renderer* renderer, SDL_Rect* sprite, int x, int y) const;
};

}  // namespace Game

#endif