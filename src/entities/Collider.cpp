#include "entities/Collider.h"
#include "entities/GameObject.h"
#include "Collider.h"

namespace Game {

bool Collider::checkCollision(const Collider& collider1, const Collider& collider2) {
	if (!collider1.active || !collider2.active) return false;

	Vector thisPos = collider1.getOwner().getPosition() + collider1.getPosition();
	Vector otherPos = collider2.getOwner().getPosition() + collider2.getPosition();

	return thisPos.x < otherPos.x + collider2.size.x &&
	       thisPos.x + collider1.size.x > otherPos.x &&
	       thisPos.y < otherPos.y + collider2.size.y &&
	       thisPos.y + collider1.size.y > otherPos.y;
}

void Collider::processCollision(Collider& collider1, Collider& collider2) {
	Object& thisObj = collider1.getOwner();
	Object& otherObj = collider2.getOwner();
	Vector thisPos = thisObj.getPosition() + collider1.getPosition();
	Vector otherPos = otherObj.getPosition() + collider2.getPosition();

	// Get the lower bounds of the overlapping rect
	float overlapLeft = std::max(thisPos.x, otherPos.x);
	float overlapTop = std::max(thisPos.y, otherPos.y);

	thisPos += collider1.getSize();
	otherPos += collider2.getSize();

	// Get the upper bounds of the overlapping rect
	float overlapRight = std::min(thisPos.x, otherPos.x);
	float overlapBottom = std::min(thisPos.y, otherPos.y);

	float overlapWidth = overlapRight - overlapLeft;
	float overlapHeight = overlapBottom - overlapTop;

	// Move the objects apart
	Vector separationVector;
	if (overlapWidth < overlapHeight) {
		separationVector = Vector(overlapWidth / 2, 0);
		if (thisPos.x > otherPos.x) {
			separationVector *= -1.0f;  // Move left object left and right object right
		}
	} else {
		separationVector = Vector(0, overlapHeight / 2);
		if (thisPos.y > otherPos.y) {
			separationVector *= -1.0f;  // Move top object up and bottom object down
		}
	}

	if (collider1.isPush() && collider2.isPush()) {
		if (!collider1.isFixed()) {
			thisObj.setPosition(thisObj.getPosition() - separationVector);
		} else {
			otherObj.setPosition(otherObj.getPosition() + separationVector);
		}

		if (!collider2.isFixed()) {
			otherObj.setPosition(otherObj.getPosition() + separationVector);
		} else {
			thisObj.setPosition(thisObj.getPosition() - separationVector);
		}
	}

	// Run the callbacks
	collider1.onCollision(collider2);
	collider2.onCollision(collider1);
}

}  // namespace Game
