#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include <SDL2/SDL.h>

#include "graphics/Atlas.h"

namespace Game {

struct AnimationFrame {
	Sprite sprite;
	float duration;  // in seconds
};

// This class is responsible for managing all the animations of a sprite.
class Animation {
   protected:
	std::vector<std::vector<AnimationFrame>> animations;
	int currentAnimation = 0;
	int currentFrame = 0;
	float frameTime = 0;
	int direction = 0;

   public:
	void addAnimation(const std::vector<AnimationFrame>& animation);

	// This is a helper function to add an entire animation based on the position of the first sprite.
	// This assumes that the sprites are laid horizontally, such that a row contains all the sprites for a single animation
	void addAnimation(const Sprite first, const std::vector<float> frameTimes);

	Sprite getCurrentSprite();

	void setAnimation(const int index) {
		if (index == currentAnimation) return;
		currentAnimation = index;
		reset();
	}

	void setDirection(const int direction) {
		this->direction = direction;
	}

	void update(const float dt);
	void reset();
};

}  // namespace Game

#endif