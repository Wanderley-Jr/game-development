#ifndef COLLIDER_H
#define COLLIDER_H

#include <functional>

#include "Utils.h"

namespace Game {

class Object;

class Collider {
   protected:
	std::string name;
	Object& owner;
	Vector position;
	Vector size;
	bool fixed;
	bool push;
	std::function<void(Collider&)> callback;

   public:
	const std::string& getName() const { return name; }
	const Vector& getPosition() const { return position; }
	const Vector& getSize() const { return size; }
	const bool isFixed() const { return fixed; }
	const bool isPush() const { return push; }

	Object& getOwner() const { return owner; }

	Collider(
	    std::string name,
	    Object& owner,
	    Vector position,
	    Vector size,
	    bool fixed,  // If fixed, this object will not be moved
	    bool push,   // If push, the other object will be pushed
	    std::function<void(Collider&)> callback) : name(std::move(name)),
	                                               owner(owner),
	                                               position(position),
	                                               size(size),
	                                               fixed(fixed),
	                                               callback(callback),
	                                               push(push) {}

	void onCollision(Collider& other) {
		callback(other);
	}

	static bool checkCollision(const Collider& collider1, const Collider& collider2);
	static void processCollision(Collider& collider1, Collider& collider2);
};

}  // namespace Game

#endif  // COLLIDER_H