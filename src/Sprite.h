#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <SDL.h>

namespace Game {

// Class responsible for managing sprites using a spritesheet.
class Sprite {
   private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect clipRect;

   public:
	Sprite(SDL_Renderer* renderer, const char* filename, int x, int y);
	~Sprite();

	void select(int x, int y);
	void render(SDL_Renderer* renderer, int x, int y);
};

}  // namespace Game

#endif