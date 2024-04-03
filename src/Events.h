#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

#include <my-lib/trigger.h>

#include "Direction.h"

namespace Game {
namespace Events {

struct UpdateDirectionEvent {
	Direction direction;
	bool start;
};

using UpdateDirection = Mylib::Trigger::EventHandler<UpdateDirectionEvent>;

inline UpdateDirection playerMove;

void processEvents();

}  // namespace Events
}  // namespace Game

#endif