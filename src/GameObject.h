#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <my-lib/math-vector.h>

#include "Events.h"
#include "Direction.h"
#include "Sprite.h"

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

class Object {
   protected:
	Vector position;
	Vector speed;
	Vector translate;
	Direction direction;

   public:
	Vector getPosition();
	Vector getSpeed();
	Direction getDirection();
	void setPosition(const Vector position);
	void setSpeed(const Vector speed);
	void setDirection(Direction direction);

	Object(const float x, const float y);

	void physics(const float dt);
	virtual void render(SDL_Renderer* renderer, int tileSize) = 0;
};

}  // namespace Game

#endif
