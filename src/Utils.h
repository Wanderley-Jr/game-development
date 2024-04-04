#ifndef UTILS_H
#define UTILS_H

#include "Direction.h"
#include <my-lib/math-vector.h>

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

namespace Utils {

Vector getDirectionVector(Direction direction);

}  // namespace Utils
}  // namespace Game

#endif