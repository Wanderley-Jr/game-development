#include <stdexcept>

#include <SDL.h>
#include <SDL_image.h>

#include "graphics/Atlas.h"

namespace Game {

Atlas::Atlas(SDL_Renderer* renderer, const char* filename) : renderer(renderer) {
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == nullptr) {
		throw std::runtime_error("Failed to load image: " + std::string(IMG_GetError()));
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
	}

	SDL_FreeSurface(surface);
}

Atlas::~Atlas() {
	SDL_DestroyTexture(texture);
}

void Atlas::render(const Sprite sprite, const int x, const int y) const {
	SDL_Rect atlasRegion = {sprite.x, sprite.y, sprite.width, sprite.height};
	SDL_Rect dest = {x - sprite.originX, y - sprite.originY, sprite.width, sprite.height};
	SDL_RenderCopy(renderer, texture, &atlasRegion, &dest);
}

}  // namespace Game