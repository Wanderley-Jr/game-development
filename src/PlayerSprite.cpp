#include "Atlas.h"
#include "PlayerSprite.h"

namespace Game {

PlayerSprite::PlayerSprite(const Atlas& atlas) : atlas(atlas), direction(Direction::DOWN), state(State::STANDING) {
	// Walk animation
	Animation walk;
	walk.addFrame({Sprite::PLAYER_STANDING, 0.2});
	walk.addFrame({Sprite::PLAYER_WALKING_1, 0.2});
	walk.addFrame({Sprite::PLAYER_STANDING, 0.2});
	walk.addFrame({Sprite::PLAYER_WALKING_2, 0.2});
	animations[State::WALKING] = walk;

	// Attack animation
	Animation attack;
	attack.addFrame({Sprite::PLAYER_ATTACKING_1, 0.1});
	attack.addFrame({Sprite::PLAYER_ATTACKING_2, 0.3});
	attack.addFrame({Sprite::PLAYER_ATTACKING_1, 0.1});
	animations[State::ATTACKING] = attack;

	// Standing animation
	Animation standing;
	standing.addFrame({Sprite::PLAYER_STANDING, -1});
	animations[State::STANDING] = standing;
}

void PlayerSprite::render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect sprite = animations[state].getCurrentSprite();

	// Calculate the correct origin of the sprite
	int shiftX = 0, shiftY = 0;

	switch (state) {
	case State::STANDING:
	case State::WALKING:
		shiftY = -8;
		break;
	case State::ATTACKING:
		shiftX = -8;
		shiftY = -11;
		break;
	}

	if (sprite.w != 16) {
		shiftX = -8;
		shiftY = -11;
	}

	// Adjust the sprite position based on the direction, which works
	// because the character sprites are put adjacently in the atlas
	sprite.x += ((int)direction) * sprite.w;

	atlas.render(renderer, &sprite, x + shiftX, y + shiftY);
}

void PlayerSprite::update(float dt) {
	animations[state].update(dt);
}

}  // namespace Game