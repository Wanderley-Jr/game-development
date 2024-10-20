#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include <my-lib/matrix.h>

#include "graphics/Atlas.h"
#include "entities/GameObject.h"
#include "entities/Player.h"
#include "entities/Tile.h"

namespace Game {

class Player;

class World {
   protected:
	const Atlas& atlas;
	Mylib::Matrix<Tile*> map;
	std::vector<Object*> objects;
	Player* player;
	float width;
	float height;

   public:
	float getWidth() const {
		return width;
	}

	float getHeight() const {
		return height;
	}

	const std::vector<Object*>& getObjects() const {
		return objects;
	}

	const Player* getPlayer() const {
		return player;
	}

	World(const Atlas& atlas);

	~World();

	void reset();

	void spawnEnemy();

	void processPhysics(const float dt);
	void processTileCollisions();
	void processEntityCollisions();

	void render(SDL_Renderer* renderer, const float dt);
};

}  // namespace Game

#endif