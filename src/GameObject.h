#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

#include "Events.h"
#include "Direction.h"
#include "Sprite.h"

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

class Object {
   protected:
	Vector position;
	Vector speed;

   public:
	Object(const float x, const float y);

	virtual void render(SDL_Renderer* renderer, int tileSize) = 0;
	virtual void physics(const float dt);
};

}  // namespace Game

#endif
