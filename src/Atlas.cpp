#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>

#include "Atlas.h"

namespace Game {

#include <stdio.h>
#include <SDL_surface.h>

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
	// printf("Destructor has been called\n");
	// SDL_DestroyTexture(texture);
}

void Atlas::render(SDL_Renderer* renderer, SDL_Rect* sprite, int x, int y) const {
	SDL_Rect dest = {x, y, sprite->w, sprite->h};
	SDL_RenderCopy(renderer, texture, sprite, &dest);
}

}  // namespace Game