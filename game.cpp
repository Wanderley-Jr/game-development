#include <SDL.h>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;

struct {
	int x;
	int y;
	int width;
	int height;
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

	rect.x += directions[0] * 50;
	rect.y += directions[1] * 50;
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

int main() {
	if (!initializeWindow()) return -1;

	rect.width = rect.height = 24;
	rect.x = (SCREEN_WIDTH - rect.width)/2;
	rect.y = (SCREEN_HEIGHT - rect.height)/2;

	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
				break;
			}
			else if (e.type == SDL_KEYDOWN) {
				handleKeyPress(e.key.keysym.sym);
			}
			
			render();
		}
	}
}