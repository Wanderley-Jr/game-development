#ifndef ATLAS_H
#define ATLAS_H

#include <SDL.h>

namespace Game {

struct Sprite {
	int x;
	int y;
	int width;
	int height;
	int originX;
	int originY;
};

namespace Sprites {
const Sprite PLAYER_STANDING = {.x = 0, .y = 0, .width = 16, .height = 24, .originX = 0, .originY = 8};
const Sprite PLAYER_WALKING_1 = {.x = 0, .y = 24, .width = 16, .height = 24, .originX = 0, .originY = 8};
const Sprite PLAYER_WALKING_2 = {.x = 0, .y = 48, .width = 16, .height = 24, .originX = 0, .originY = 8};
const Sprite PLAYER_ATTACKING_1 = {.x = 0, .y = 72, .width = 32, .height = 32, .originX = 8, .originY = 11};
const Sprite PLAYER_ATTACKING_2 = {.x = 0, .y = 104, .width = 32, .height = 32, .originX = 8, .originY = 11};
}  // namespace Sprites

// Class responsible for managing all sprites.
class Atlas {
   private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;

   public:
	Atlas(SDL_Renderer* renderer, const char* filename);
	~Atlas();

	void render(const Sprite sprite, const int x, const int y) const;
};

}  // namespace Game

#endif