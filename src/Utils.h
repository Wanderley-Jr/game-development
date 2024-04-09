#ifndef UTILS_H
#define UTILS_H

#include <my-lib/math-vector.h>

#include "Direction.h"

using Vector = Mylib::Math::Vector<float, 2>;

namespace Game {

namespace Utils {

Vector toDirectionVector(Vector direction);
Vector toDirectionVector(Direction direction);

}  // namespace Utils
}  // namespace Game

#endif