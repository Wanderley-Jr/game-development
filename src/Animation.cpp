#include "Animation.h"

namespace Game {

void Animation::addAnimation(const std::vector<AnimationFrame>& animation) {
	animations.push_back(animation);
}

void Animation::setAnimation(const int index) {
	currentAnimation = index;
}

Sprite Animation::getCurrentSprite() {
	if (currentFrame != 0) {
		printf("currentAnimation: %d\n", currentAnimation);
		printf("currentFrame: %d\n", currentFrame);
		printf("frameTime: %f\n", frameTime);
		printf("sprite: %p\n", &animations[currentAnimation][currentFrame].sprite);
		printf("duration: %f\n", animations[currentAnimation][currentFrame].duration);
	}

	return animations[currentAnimation][currentFrame].sprite;
}

void Animation::update(const float dt) {
	frameTime += dt;

	float duration = animations[currentAnimation][currentFrame].duration;
	if (frameTime >= duration) {
		frameTime -= duration;
		currentFrame++;

		if (currentFrame >= animations[currentAnimation].size()) {
			currentFrame = 0;
		}
	}

	printf("Current index: %d\n", currentAnimation);
	printf("Current frame: %d\n", currentFrame);
}

void Animation::reset() {
	currentFrame = 0;
	frameTime = 0;
}

}  // namespace Game
