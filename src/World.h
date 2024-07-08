#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <SDL.h>

#include <my-lib/matrix.h>

#include "entities/GameObject.h"
#include "graphics/Atlas.h"
#include "entities/Player.h"

namespace Game {

enum class Tile {
	GRASS,
	WALL
};

class World {
   protected:
	const Atlas& atlas;
	Mylib::Matrix<Tile> map;
	std::vector<Object*> objects;
	int width;   // float
	int height;  // float

   public:
	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

	World(const Atlas& atlas);

	void processPhysics(const float dt);
	void processTileCollisions();
	void processEntityCollisions();

	void render(SDL_Renderer* renderer, const float dt);
};

}  // namespace Game

#endif