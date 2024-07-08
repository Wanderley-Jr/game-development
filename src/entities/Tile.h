#pragma once

#include "entities/GameObject.h"
#include "graphics/Atlas.h"

namespace Game {

class Tile : public Object {
   public:
	enum Type { GRASS,
		        WALL };

	const Atlas& atlas;
	const Sprite sprite;

	// TODO: replace color with sprite
	Tile(const std::string name, const Atlas& atlas, const Sprite sprite, const bool solid, const float x, const float y);

	void render(const Atlas& atlas, const float dt, const int x, const int y) override;
};

}  // namespace Game