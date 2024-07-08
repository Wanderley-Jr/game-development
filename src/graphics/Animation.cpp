#include "graphics/Animation.h"

namespace Game {

void Animation::addAnimation(const std::vector<AnimationFrame>& animation) {
	animations.push_back(animation);
}

void Animation::addAnimation(const Sprite first, const std::vector<float> frameTimes) {
	std::vector<AnimationFrame> animation;
	for (int j = 0; j < frameTimes.size(); j++) {
		AnimationFrame frame;
		frame.sprite = first;
		frame.sprite.x += first.width * j;
		frame.duration = frameTimes[j];
		animation.push_back(frame);
	}
	animations.push_back(animation);
}

Sprite Animation::getCurrentSprite() {
	Sprite sprite = animations[currentAnimation][currentFrame].sprite;
	sprite.y += sprite.height * direction;
	return sprite;
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
}

void Animation::reset() {
	currentFrame = 0;
	frameTime = 0;
}

}  // namespace Game
