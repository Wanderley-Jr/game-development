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

using Attack = Mylib::Trigger::EventHandler<void*>;
inline Attack playerAttack;

using Dash = Mylib::Trigger::EventHandler<void*>;
inline Dash playerDash;

void processEvents();

}  // namespace Events
}  // namespace Game

#endif