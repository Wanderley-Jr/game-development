#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SDL.h>

#include <my-lib/matrix.h>

namespace Game {

enum class Tile {
	GRASS,
	WATER
};

class Map {
   private:
	Mylib::Matrix<Tile> map;
	int width;
	int height;

   public:
	Map();
	void render(SDL_Renderer* renderer, int tileSize);
	int getWidth();
	int getHeight();
};

}  // namespace Game

#endif