#include <SDL.h>
#include <SDL_image.h>

#include "entities/GameObject.h"
#include "entities/Player.h"
#include "Events.h"
#include "World.h"

SDL_Window* window = NULL;

bool initializeWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	printf("SDL has been initialized\n");

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	printf("SDL_image has been initialized\n");

	window = SDL_CreateWindow(
	    "Game Test",
	    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	    0, 0,
	    0);

	return true;
}

int main() {
	if (!initializeWindow()) return -1;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Game::Atlas atlas = Game::Atlas(renderer, "./assets/atlas.png");
	Game::World world = Game::World(atlas);
	bool isAlive = true;

	// Scale game screen up!!!
	int tileSize = 16;
	int scale = 2;
	int windowWidth = world.getWidth() * tileSize * scale;
	int windowHeight = world.getHeight() * tileSize * scale;
	SDL_SetWindowSize(window, windowWidth, windowHeight);
	SDL_RenderSetScale(renderer, scale, scale);

	// Main loop
	Uint64 lastTick = SDL_GetTicks64();
	while (isAlive) {
		Uint64 elapsed = SDL_GetTicks64() - lastTick;
		lastTick = SDL_GetTicks64();
		float dt = elapsed / 1000.0f;

		Game::Events::processEvents();
		world.processPhysics(dt);
		world.render(renderer, dt);

		SDL_Delay(1000 / 60);
	}
}