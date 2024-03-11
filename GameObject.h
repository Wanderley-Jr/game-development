#include <my-lib/math-vector.h>

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

using Vector = Mylib::Math::Vector<float, 2>;

class GameObject {
	private:
		Vector position;
		Vector speed;
	
	public:
		GameObject();
		Vector getPosition();
		Vector getSpeed();
};

#endif
