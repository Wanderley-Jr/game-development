#include <stdio.h>

#include <SDL.h>
#include "GameObject.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;

struct {
	int x; int y;
	int width; int height;
	int speedX; int speedY;
} rect;

bool initializeWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
    }

	window = SDL_CreateWindow(
		"Game Test", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_VULKAN
	);

	return true;
}

void handleKeyPress(SDL_Keycode key) {
	int directions[2] = { 0 };

	switch (key) {
		case SDLK_UP:
			directions[1] = -1;
			break;
		case SDLK_DOWN:
			directions[1] = 1;
			break;
		case SDLK_LEFT:
			directions[0] = -1;
			break;
		case SDLK_RIGHT:
			directions[0] = 1;
			break;
		default:
			return;
	}

	rect.speedX += directions[0] * 3;
	rect.speedY += directions[1] * 3;
}

void update() {
	rect.x += rect.speedX;
	rect.y += rect.speedY;

	if (rect.x < 0) {
		rect.x = 0;
		rect.speedX *= -0.95;
	} else if (rect.x + rect.width > SCREEN_WIDTH) {
		rect.x = SCREEN_WIDTH - rect.width;
		rect.speedX *= -0.95;
	}

	if (rect.y < 0) {
		rect.y = 0;
		rect.speedY *= -0.95;
	} else if (rect.y + rect.height > SCREEN_HEIGHT) {
		rect.y = SCREEN_HEIGHT - rect.height;
		rect.speedY *= -0.95;
	}
}

void render() {
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	// Render black background
	Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
	SDL_FillRect(surface, NULL, black);

	// Render red square
	Uint32 red = SDL_MapRGB(surface->format, 255, 0, 0);
	SDL_Rect sdlRect = { rect.x, rect.y, rect.width, rect.height };
	SDL_FillRect(surface, &sdlRect, red);

	SDL_UpdateWindowSurface(window);
}

// -> Usar fator de conversão (Ex: m <=> px)
// -> Calcular distância percorrida usando a variação do tempo vezes a velocidade
// -> OOP
int main() {
	if (!initializeWindow()) return -1;

	rect.x = (SCREEN_WIDTH - rect.width)/2;
	rect.y = (SCREEN_HEIGHT - rect.height)/2;
	rect.width = rect.height = 24;
	rect.speedX = rect.speedY = 0;
	
	GameObject obj;
	printf("Position: [%f,%f]\n", obj.getPosition().x, obj.getPosition().y);;

	SDL_Event e;
	while (e.type != SDL_QUIT && false) {
		// Handle events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) break;
			
			if (e.type == SDL_KEYDOWN && !e.key.repeat) {
				handleKeyPress(e.key.keysym.sym);
			}
		}
		
		update();
		render();
		SDL_Delay(1000/60);
	}
}
