#ifndef ATLAS_H
#define ATLAS_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

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

// Player sprites
const Sprite PLAYER_WALKING_1 = {.x = 0, .y = 0, .width = 16, .height = 24, .originX = 0, .originY = 8};
const Sprite PLAYER_STANDING = {.x = 16, .y = 0, .width = 16, .height = 24, .originX = 0, .originY = 8};
const Sprite PLAYER_WALKING_2 = {.x = 32, .y = 0, .width = 16, .height = 24, .originX = 0, .originY = 8};

const Sprite PLAYER_ATTACKING = {.x = 48, .y = 0, .width = 32, .height = 32, .originX = 8, .originY = 11};

// Tile sprites
const Sprite GRASS = {.x = 112, .y = 16, .width = 16, .height = 16, .originX = 0, .originY = 0};
const Sprite DIRT = {.x = 128, .y = 16, .width = 16, .height = 16, .originX = 0, .originY = 0};

// Boar
const Sprite BOAR_WALKING = {.x = 0, .y = 128, .width = 24, .height = 24, .originX = 4, .originY = 4};
const Sprite BOAR_STANDING = {.x = 24, .y = 128, .width = 24, .height = 24, .originX = 4, .originY = 4};

// Enemy
const Sprite ENEMY = {.x = 96, .y = 48, .width = 16, .height = 16, .originX = 0, .originY = 0};

}  // namespace Sprites

// Class responsible for managing all sprites.
class Atlas {
   private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	TTF_Font* font;

   public:
	Atlas(SDL_Renderer* renderer, const char* filename);
	~Atlas();

	void render(const Sprite sprite, const int x, const int y) const;

	// render with color modifiers
	void render(const Sprite sprite, const int x, const int y, const SDL_Color& color) const;

	void render(const std::string text, const int x, const int y) const;
};

}  // namespace Game

#endif