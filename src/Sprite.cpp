#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>

#include "Sprite.h"

namespace Game {

#include <stdio.h>
#include <SDL_surface.h>

Sprite::Sprite(SDL_Renderer* renderer, const char* filename, int x, int y) : renderer(renderer), clipRect({0, 0, 0, 0}) {
	SDL_Surface* surface = IMG_Load(filename);

	if (surface == nullptr) {
		throw std::runtime_error("Failed to load image: " + std::string(IMG_GetError()));
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
	}

	clipRect.w = surface->w / 4;
	clipRect.h = surface->h / 1;

	SDL_FreeSurface(surface);
}

Sprite::~Sprite() {
	// printf("Destructor has been called\n");
	// SDL_DestroyTexture(texture);
}

void Sprite::select(int x, int y) {
	clipRect.x = x * clipRect.w;
	clipRect.y = y * clipRect.h;
}

void Sprite::render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect dest = {x, y, clipRect.w, clipRect.h};
	SDL_RenderCopy(renderer, texture, &clipRect, &dest);
}

}  // namespace Game