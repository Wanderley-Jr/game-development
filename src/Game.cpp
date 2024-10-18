#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <my-lib/trigger.h>

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

	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

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
	int windowWidth = 12 * tileSize * scale;
	int windowHeight = 12 * tileSize * scale;
	SDL_SetWindowSize(window, windowWidth, windowHeight);
	SDL_RenderSetScale(renderer, scale, scale);

	// Main loop
	Uint64 lastTick = SDL_GetTicks64();

	auto music = Mix_LoadWAV("./assets/music.mp3");
	auto gameOverSound = Mix_LoadWAV("./assets/game_over.wav");
	Mix_Volume(0, 40);
	Mix_PlayChannel(0, music, -1);

	while (isAlive) {
		Uint64 elapsed = SDL_GetTicks64() - lastTick;
		lastTick = SDL_GetTicks64();
		float dt = elapsed / 1000.0f;

		Game::Events::processEvents();
		world.processPhysics(dt);
		world.render(renderer, dt);

		// Game over
		if (world.getPlayer()->getHealth() <= 0) {
			Mix_HaltChannel(-1);
			Mix_PlayChannel(0, gameOverSound, 0);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			atlas.crender("Fim de jogo", windowWidth / 4, windowHeight / 4 - 75);
			atlas.crender("Aperte espaco para renascer...", windowWidth / 4, windowHeight / 4 + 75);

			SDL_RenderPresent(renderer);

			SDL_Event event;
			while (event.type != SDL_KEYDOWN || event.key.keysym.sym != SDLK_SPACE) {
				SDL_PollEvent(&event);
				SDL_Delay(1000 / 120);
			}

			Mix_PlayChannel(0, music, -1);
			world.reset();
		}

		SDL_Delay(1000 / 120);
	}
}