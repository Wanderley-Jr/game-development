#include "Events.h"

namespace Game {
namespace Events {

// Keyboard keyboard;

Direction toDirection(const SDL_Keycode key) {
	switch (key) {
	case SDLK_UP:
		return Direction::UP;
	case SDLK_DOWN:
		return Direction::DOWN;
	case SDLK_LEFT:
		return Direction::LEFT;
	case SDLK_RIGHT:
		return Direction::RIGHT;
	default:
		return Direction::NONE;
	}
}

void processEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		bool start = false;
		switch (event.type) {
		case SDL_KEYDOWN:
			start = true;
		case SDL_KEYUP: {
			Direction direction = toDirection(event.key.keysym.sym);
			if (direction != Direction::NONE) {
				playerMove.publish(UpdateDirectionEvent{
				    .direction = direction,
				    .start = start,
				});
			}

			if (event.key.keysym.sym == SDLK_SPACE) {
				playerAttack.publish(nullptr);
			}

			break;
		}
		case SDL_QUIT:
			exit(0);
			break;
		}
	}
}

}  // namespace Events
}  // namespace Game
