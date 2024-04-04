#include "Map.h"

#include <string>

namespace Game {

Tile getTile(char ch) {
	switch (ch) {
	case '.':
		return Tile::GRASS;
	case 'w':
		return Tile::WATER;
	default:
		return Tile::GRASS;
	}
}

Map::Map() {
	width = 11;
	height = 7;
	const char mapStr[] =
	    "..........."
	    "..........."
	    "....www...."
	    "....www...."
	    "....www...."
	    "..........."
	    "...........";

	map = Mylib::Matrix<Tile>(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			map(x, y) = getTile(mapStr[y * width + x]);
		}
	}
}

int Map::getWidth() {
	return width;
}

int Map::getHeight() {
	return height;
}

void Map::render(SDL_Renderer* renderer, int tileSize) {
	SDL_Rect rect;
	rect.w = tileSize;
	rect.h = tileSize;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			rect.x = x * tileSize;
			rect.y = y * tileSize;

			switch (map(x, y)) {
			case Tile::GRASS:
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				break;
			case Tile::WATER:
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				break;
			}

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

}  // namespace Game