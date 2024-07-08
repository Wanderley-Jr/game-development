#include "Tile.h"

namespace Game {

Tile::Tile(const std::string name, const Atlas& atlas, const Sprite sprite, const bool solid, const float x, const float y) : Object(std::move(name)), sprite(sprite), atlas(atlas) {
	if (solid) {
		colliders.push_back(Collider(name, *this, Vector(x, y), Vector(1, 1), true, true, [](Collider& other) {
			other.getOwner().setSpeed(Vector::zero());
		}));
	}
}

void Tile::render(const Atlas& atlas, const float dt, const int x, const int y) {
	atlas.render(sprite, x, y);
}

}  // namespace Game