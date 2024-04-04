#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

#include <chrono>
#include <my-lib/trigger.h>
#include <my-lib/timer.h>

#include "Direction.h"

namespace Game {
namespace Events {

struct UpdateDirectionEvent {
	Direction direction;
	bool start;
};

using UpdateDirection = Mylib::Trigger::EventHandler<UpdateDirectionEvent>;
using Attack = Mylib::Trigger::EventHandler<void*>;

inline UpdateDirection playerMove;
inline Attack playerAttack;

void processEvents();

}  // namespace Events
}  // namespace Game

#endif