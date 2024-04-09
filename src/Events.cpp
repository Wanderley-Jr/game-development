#include "Events.h"

namespace Game {
namespace Events {

Direction toDirection(const SDL_Keycode key) {
	// WASD
	switch (key) {
	case SDLK_w:
		return Direction::UP;
	case SDLK_a:
		return Direction::LEFT;
	case SDLK_s:
		return Direction::DOWN;
	case SDLK_d:
		return Direction::RIGHT;
	default:
		return Direction::NONE;
	}
}

void processEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP: {
			Direction direction = toDirection(event.key.keysym.sym);
			if (direction != Direction::NONE) {
				playerMove.publish(UpdateDirectionEvent{
				    .direction = direction,
				    .start = event.type == SDL_KEYDOWN,
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
