#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include <SDL.h>

#include "Sprite.h"

namespace Game {

struct AnimationFrame {
	Sprite sprite;
	float duration;  // in seconds
};

class Animation {
   protected:
	std::vector<std::vector<AnimationFrame>> animations;
	int currentAnimation;
	int currentFrame;
	float frameTime;

   public:
	Animation() : currentAnimation(0), currentFrame(0), frameTime(0){};

	void addAnimation(const std::vector<AnimationFrame>& animation);

	Sprite getCurrentSprite();
	void setAnimation(const int index);
	void update(const float dt);
	void reset();
};

}  // namespace Game

#endif