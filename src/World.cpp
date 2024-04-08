#include "World.h"
#include "Player.h"

namespace Game {

const int TILE_SIZE = 16;

void initializeMap(Mylib::Matrix<Tile>& map, const std::string& mapStr) {
	int width = map.get_nrows();
	int height = map.get_ncols();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Tile tile;
			switch (mapStr[y * width + x]) {
			case '.':
				tile = Tile::GRASS;
				break;
			case 'w':
				tile = Tile::WATER;
				break;
			default:
				tile = Tile::GRASS;
				break;
			}
			map(x, y) = tile;
		}
	}
}

void renderMap(SDL_Renderer* renderer, const Mylib::Matrix<Tile>& map) {
	SDL_Rect rect;
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;

	for (int y = 0; y < map.get_ncols(); y++) {
		for (int x = 0; x < map.get_nrows(); x++) {
			rect.x = x * TILE_SIZE;
			rect.y = y * TILE_SIZE;

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

World::World(const Atlas& atlas) : atlas(atlas) {
	width = 11;
	height = 7;
	map = Mylib::Matrix<Tile>(width, height);

	initializeMap(
	    map,
	    "..........."
	    "..........."
	    "....www...."
	    "....www...."
	    "....www...."
	    "..........."
	    "...........");

	objects.push_back(new Player(atlas, 0, 0));
}

void World::processPhysics(const float dt) {
	for (auto& object : objects) {
		object->physics(dt);
	}
}

void World::render(SDL_Renderer* renderer, const float dt) {
	renderMap(renderer, map);

	for (auto& object : objects) {
		Vector position = object->getPosition();
		position *= TILE_SIZE;
		object->render(renderer, dt, (int)position.x, (int)position.y);
	}

	SDL_RenderPresent(renderer);
}

}  // namespace Game