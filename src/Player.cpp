#include <SDL.h>

#include "Player.h"
#include "Utils.h"

namespace Game {

void Player::render(SDL_Renderer* renderer, int tileSize) {
	switch (direction) {
	case Direction::DOWN:
		sprite.select(0, 0);
		break;
	case Direction::UP:
		sprite.select(1, 0);
		break;
	case Direction::LEFT:
		sprite.select(2, 0);
		break;
	case Direction::RIGHT:
		sprite.select(3, 0);
		break;
	}

	Vector pos = position + translate;
	sprite.render(renderer, (int)(pos.x * tileSize), (int)(pos.y * tileSize));
}

Player::Player(Sprite sprite, float x, const float y) : Object(x, y), sprite(sprite) {
	// Subscribe to keyboard events
	auto callback = Mylib::Trigger::make_callback_object<Events::Keyboard::Type>(*this, &Player::onKeyPress);
	Events::keyboard.subscribe(callback);
}

void Player::onKeyPress(const Events::Keyboard::Type& key) {
	// If the player is already moving, ignore the key press
	if (translate.length() != 0) return;

	Direction oldDirection = direction;

	// Otherwise, make him turn
	switch (key) {
	case SDLK_UP:
		direction = Direction::UP;
		break;
	case SDLK_DOWN:
		direction = Direction::DOWN;
		break;
	case SDLK_LEFT:
		direction = Direction::LEFT;
		break;
	case SDLK_RIGHT:
		direction = Direction::RIGHT;
		break;
	default:
		break;
	}

	// If player was already facing that direction, move
	if (oldDirection == direction) {
		speed = Utils::getDirectionVector(direction) * 3.5f;
	}
	// Otherwise, he simply turns into that direction
}

}  // namespace Game