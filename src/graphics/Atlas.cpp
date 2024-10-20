#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

	font = TTF_OpenFont("./assets/font.ttf", 12);
	if (font == nullptr) {
		throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
	}
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

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

void Atlas::render(const Sprite sprite, const int x, const int y, const SDL_Color& color) const {
	Uint8 alpha;
	SDL_GetTextureAlphaMod(texture, &alpha);
	Uint8 r, g, b;
	SDL_GetTextureColorMod(texture, &r, &g, &b);

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);

	render(sprite, x, y);

	SDL_SetTextureColorMod(texture, r, g, b);
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Atlas::render(const std::string text, const int x, const int y) const {
	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dest = {x, y - h / 2, surface->w, surface->h};
	SDL_RenderCopy(renderer, textTexture, nullptr, &dest);
}

void Atlas::crender(const std::string text, const int x, const int y) const {
	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dest = {x - w / 2, y - h / 2, surface->w, surface->h};
	SDL_RenderCopy(renderer, textTexture, nullptr, &dest);
}

}  // namespace Game