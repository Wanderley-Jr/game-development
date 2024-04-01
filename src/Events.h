#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

#include <my-lib/trigger.h>

namespace Game {
namespace Events {

using Keyboard = Mylib::Trigger::EventHandler<SDL_Keycode>;

extern Keyboard keyboard;

}  // namespace Events
}  // namespace Game

#endif