#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "Player.h"
#include "Events.h"
#include "PlayerSprite.h"
#include "Map.h"

using namespace std;

SDL_Window* window = NULL;

Game::Map map;
std::vector<Game::Object*> gameObjects;

const int TILE_SIZE = 16;
const int SCALE = 2;
const int SCREEN_WIDTH = map.getWidth() * TILE_SIZE * SCALE;
const int SCREEN_HEIGHT = map.getHeight() * TILE_SIZE * SCALE;

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
	    SCREEN_WIDTH, SCREEN_HEIGHT,
	    0);

	return true;
}

void render(const float dt) {
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_RenderClear(renderer);

	SDL_RenderSetScale(renderer, SCALE, SCALE);

	map.render(renderer, TILE_SIZE);

	// render all game objects
	for (auto& obj : gameObjects) {
		obj->render(renderer, dt, TILE_SIZE);
	}

	SDL_RenderPresent(renderer);
}

int main() {
	if (!initializeWindow()) return -1;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderTarget(renderer, NULL);

	Game::Atlas atlas = Game::Atlas(renderer, "./assets/atlas.png");
	Game::Atlas playerSprite(atlas);
	Game::Player* player = new Game::Player(playerSprite, 0, 0);
	gameObjects.push_back(player);

	Uint64 lastTick = SDL_GetTicks64();

	SDL_Event e;
	while (e.type != SDL_QUIT) {
		// Calculate delta time
		float dt = (SDL_GetTicks64() - lastTick) / 1000.0f;
		lastTick = SDL_GetTicks64();

		// check for keyboard events
		Game::Events::processEvents();
		player->physics(dt);
		render(dt);

		SDL_Delay(1000 / 60);
	}
}
