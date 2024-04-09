#ifndef UTILS_H
#define UTILS_H

#include <my-lib/math-vector.h>

#include "Direction.h"

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

namespace Utils {

void toDirectionVector(Vector& direction);
Vector getDirectionVector(Direction direction);

}  // namespace Utils
}  // namespace Game

#endif