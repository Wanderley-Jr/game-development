#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <my-lib/math-vector.h>

#include "Events.h"
#include "Direction.h"
#include "Collider.h"
#include "Utils.h"
#include "graphics/Atlas.h"

using std::string;

namespace Game {

class Object {
   protected:
	const string name;
	Vector position;
	Vector speed;
	std::vector<Collider> colliders;

   public:
	const string& getName() const { return name; }

	Vector getPosition() const { return position; }
	void setPosition(const Vector& position) { this->position = position; }

	Vector getSpeed() const { return speed; }
	void setSpeed(const Vector& speed) { this->speed = speed; }

	std::vector<Collider> getColliders() const { return colliders; }

	Object(const string name) : name(std::move(name)),
	                            position(Vector::zero()),
	                            speed(Vector::zero()){};

	virtual void render(const Atlas& atlas, const float dt, const int x, const int y) {}
	virtual void update(const float dt);
};

}  // namespace Game

#endif
