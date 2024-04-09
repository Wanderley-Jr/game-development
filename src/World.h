#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <SDL.h>

#include <my-lib/matrix.h>

#include "GameObject.h"
#include "Atlas.h"
#include "Player.h"

namespace Game {

enum class Tile {
	GRASS,
	WATER
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
	void render(SDL_Renderer* renderer, const float dt);
};

}  // namespace Game

#endif