#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL.h>

#include "Atlas.h"

namespace Game {

struct AnimationFrame {
	SDL_Rect sprite;
	float duration;  // in seconds
};

class Animation {
   protected:
	std::vector<AnimationFrame> frames;
	int currentFrame;
	float frameTime;

   public:
	Animation();
	void addFrame(AnimationFrame frame);
	SDL_Rect getCurrentSprite();
	void update(float dt);
	void reset();
};

}  // namespace Game

#endif