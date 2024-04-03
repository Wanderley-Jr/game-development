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
		switch (event.type) {
		case SDL_KEYDOWN:
			playerMove.publish(UpdateDirectionEvent{
			    .direction = toDirection(event.key.keysym.sym),
			    .start = true,
			});
			break;
		case SDL_KEYUP:
			playerMove.publish(UpdateDirectionEvent{
			    .direction = toDirection(event.key.keysym.sym),
			    .start = false,
			});
			break;
		case SDL_QUIT:
			exit(0);
			break;
		}
	}
}

}  // namespace Events
}  // namespace Game
