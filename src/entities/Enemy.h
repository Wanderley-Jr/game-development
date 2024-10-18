#include <SDL.h>

#include "World.h"
#include "entities/GameObject.h"
#include "entities/Character.h"

namespace Game {

class Enemy : public Character {
   private:
	int aiStatus = 0;
	float aiDelay = 0;
	Animation animation;

	Mix_Chunk* attackSound;
	Mix_Chunk* hurtSound;

   public:
	Enemy(const string name, const World* world);

	void render(const Atlas& atlas, const float dt, const int x, const int y) override;
	void update(const float dt) override;
	void ai(const float dt) override;
};

}  // namespace Game