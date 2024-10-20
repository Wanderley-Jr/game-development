#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <my-lib/math-vector.h>

#include "Direction.h"

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

namespace Utils {

Direction toDirection(Vector vector);
Vector toDirectionVector(Vector direction);
Vector toDirectionVector(Direction direction);

}  // namespace Utils
}  // namespace Game

#endif