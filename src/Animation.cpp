#include "Animation.h"

namespace Game {

Animation::Animation() : currentFrame(0), frameTime(0) {}

void Animation::addFrame(AnimationFrame frame) {
	frames.push_back(frame);
}

void Animation::update(float dt) {
	frameTime += dt;

	float duration = frames[currentFrame].duration;
	if (duration != -1 && frameTime >= duration) {
		frameTime -= duration;
		currentFrame = (currentFrame + 1) % frames.size();
	}
}

void Animation::reset() {
	currentFrame = 0;
	frameTime = 0;
}

SDL_Rect Animation::getCurrentSprite() {
	return frames[currentFrame].sprite;
}

}  // namespace Game
