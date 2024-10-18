#include "World.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Tile.h"

namespace Game {

const int TILE_SIZE = 16;

void initializeMap(Mylib::Matrix<Tile*>& map, const Atlas& atlas, const std::string& mapStr) {
	int width = map.get_nrows();
	int height = map.get_ncols();

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			switch (mapStr[y * width + x]) {
			case 'w':
				map(x, y) = new Tile("BUSH", atlas, Sprites::BUSH, true, x, y);
				break;
			case 'a':
				map(x, y) = new Tile("WINDOW_1", atlas, Sprites::WINDOW_1, true, x, y);
				break;
			case 'b':
				map(x, y) = new Tile("WINDOW_2", atlas, Sprites::WINDOW_2, true, x, y);
				break;
			case 'c':
				map(x, y) = new Tile("DOOR_1", atlas, Sprites::DOOR_1, true, x, y);
				break;
			case 'd':
				map(x, y) = new Tile("DOOR_2", atlas, Sprites::DOOR_2, true, x, y);
				break;
			case 'e':
				map(x, y) = new Tile("WALL_1", atlas, Sprites::WALL_1, true, x, y);
				break;
			case 'f':
				map(x, y) = new Tile("WALL_2", atlas, Sprites::WALL_2, true, x, y);
				break;
			case 'g':
				map(x, y) = new Tile("WALL_3", atlas, Sprites::WALL_3, true, x, y);
				break;
			case 'h':
				map(x, y) = new Tile("ROOF_1", atlas, Sprites::ROOF_1, true, x, y);
				break;
			case 'i':
				map(x, y) = new Tile("ROOF_2", atlas, Sprites::ROOF_2, true, x, y);
				break;
			case 'j':
				map(x, y) = new Tile("ROOF_3", atlas, Sprites::ROOF_3, true, x, y);
				break;
			case 'k':
				map(x, y) = new Tile("ROOF_4", atlas, Sprites::ROOF_4, false, x, y);
				break;
			case 'l':
				map(x, y) = new Tile("DIRT", atlas, Sprites::DIRT, false, x, y);
				break;
			default:
				map(x, y) = nullptr;
				break;
			}
		}
	}
}

void renderMap(const Atlas& atlas, Vector camPos, const Mylib::Matrix<Tile*>& map) {
	for (int y = 0; y < map.get_ncols(); y++) {
		for (int x = 0; x < map.get_nrows(); x++) {
			Vector pos = Vector(x, y) - camPos;
			pos *= TILE_SIZE;

			// Render grass tiles on background
			atlas.render(Sprites::GRASS, pos.x, pos.y);

			if (map(x, y) != nullptr) {
				map(x, y)->render(atlas, 0, pos.x, pos.y);
			}
		}
	}
}

World::World(const Atlas& atlas) : atlas(atlas) {
	width = 30;
	height = 15;
	map = Mylib::Matrix<Tile*>(width, height);

	initializeMap(
	    map,
	    atlas,
	    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
	    "w                            w"
	    "w                            w"
	    "w         hijk  hijk         w"
	    "w         ecag  ecag         w"
	    "w      wwwedbgwwedbgwww      w"
	    "wllllllllllllllllllllllllllllw"
	    "w                            w"
	    "w                            w"
	    "w                            w"
	    "w   w                    w   w"
	    "w   w                    w   w"
	    "w   wwwwwwwwwwwwwwwwwwwwww   w"
	    "w                            w"
	    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwww");

	reset();
}

void World::reset() {
	objects.clear();

	player = new Player(atlas, this);
	player->setPosition(Vector(1, 1));
	objects.push_back(player);
}

void World::processTileCollisions() {
	for (auto& object : objects) {
		Vector pos = object->getPosition();

		float startX = std::max(pos.x, 0.0f);
		float startY = std::max(pos.y, 0.0f);
		float endX = std::min(width, pos.x + 1);
		float endY = std::min(height, pos.y + 1);

		for (float x = startX; x <= endX; x++) {
			for (float y = startY; y <= endY; y++) {
				for (auto& collider1 : object->getColliders()) {
					if (map(x, y) == nullptr) continue;
					for (auto& collider2 : map(x, y)->getColliders()) {
						if (Collider::checkCollision(collider1, collider2)) {
							Collider::processCollision(collider1, collider2);
						}
					}
				}
			}
		}
	}
}

void World::processEntityCollisions() {
	for (int i = 0; i < objects.size(); i++) {
		for (int j = i + 1; j < objects.size(); j++) {
			Object* object1 = objects[i];
			Object* object2 = objects[j];

			for (auto& collider1 : object1->getColliders()) {
				for (auto& collider2 : object2->getColliders()) {
					if (Collider::checkCollision(collider1, collider2)) {
						Collider::processCollision(collider1, collider2);
					}
				}
			}
		}
	}
}

void World::processPhysics(const float dt) {
	int enemyCount = 0;

	// Remove all enemies with zero health
	auto it = std::remove_if(objects.begin(), objects.end(), [](auto& object) {
		Enemy* enemy = dynamic_cast<Enemy*>(object);
		if (enemy == nullptr) return false;
		return enemy->getHealth() <= 0;
	});
	objects.erase(it, objects.end());

	for (auto& object : objects) {
		object->update(dt);

		Enemy* enemy = dynamic_cast<Enemy*>(object);
		if (enemy != nullptr) {
			enemyCount++;
		}
	}

	if (enemyCount < 1) {
		spawnEnemy();
	}

	processTileCollisions();
	processEntityCollisions();
}

void World::spawnEnemy() {
	// Spawn new enemy in the furthest of 4 corners of the map,
	// to ensure he doesn't see the enemy popping up
	Vector corners[] = {{1, 1}, {28, 1}, {1, 13}, {28, 13}};
	Vector furthest;
	double furthestDist = 0;
	for (int i = 0; i < 4; i++) {
		Vector distance = corners[i] - player->getPosition();
		if (distance.length() >= furthestDist) {
			furthest = corners[i];
			furthestDist = distance.length();
		}
	}

	Game::Enemy* enemy = new Enemy("enemy", this);
	enemy->setPosition(furthest);
	objects.push_back(enemy);
}

void renderHitbox(SDL_Renderer* renderer, Vector camPos, Object& object) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	for (auto& collider : object.getColliders()) {
		if (!collider.isActive()) continue;

		Vector pos = collider.getPosition() + object.getPosition() - camPos;
		pos *= TILE_SIZE;
		Vector size = collider.getSize();
		size *= TILE_SIZE;
		SDL_Rect rect = {(int)round(pos.x), (int)round(pos.y), (int)round(size.x), (int)round(size.y)};
		SDL_RenderDrawRect(renderer, &rect);
	}
}

// void renderCollisionHitbox(SDL_Renderer* renderer, const Vector camPos, const Collider& collider1, const Collider& collider2) {
// 	Object& thisObj = collider1.getOwner();
// 	Object& otherObj = collider2.getOwner();
// 	Vector thisPos = thisObj.getPosition() + collider1.getPosition() - camPos;
// 	Vector otherPos = otherObj.getPosition() + collider2.getPosition() - camPos;

// 	// Get the lower bounds of the overlapping rect
// 	float overlapLeft = std::max(thisPos.x, otherPos.x);
// 	float overlapTop = std::max(thisPos.y, otherPos.y);

// 	thisPos += collider1.getSize();
// 	otherPos += collider2.getSize();

// 	// Get the upper bounds of the overlapping rect
// 	float overlapRight = std::min(thisPos.x, otherPos.x);
// 	float overlapBottom = std::min(thisPos.y, otherPos.y);

// 	float overlapWidth = overlapRight - overlapLeft;
// 	float overlapHeight = overlapBottom - overlapTop;

// 	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
// 	SDL_Rect rect = {(int)round(overlapLeft * TILE_SIZE), (int)round(overlapTop * TILE_SIZE), (int)round(overlapWidth * TILE_SIZE), (int)round(overlapHeight * TILE_SIZE)};
// 	SDL_RenderDrawRect(renderer, &rect);
// }

void World::render(SDL_Renderer* renderer, const float dt) {
	// Set camera position
	Vector camPos = player->getPosition() + Vector(0.5f, 1);  // Center on the exact middle of the player
	Vector camSize = Vector(12, 12);                          // Camera size in tiles
	camPos -= camSize * 0.5f;
	camPos.x = std::max(0.0f, std::min(width - camSize.x, camPos.x));
	camPos.y = std::max(0.0f, std::min(height - camSize.y, camPos.y));

	renderMap(atlas, camPos, map);

	// Sort objects by y position
	std::sort(objects.begin(), objects.end(), [](Object* a, Object* b) {
		return a->getPosition().y < b->getPosition().y;
	});

	for (auto& object : objects) {
		Vector position = object->getPosition() - camPos;
		position *= TILE_SIZE;
		object->render(atlas, dt, (int)round(position.x), (int)round(position.y));
	}

	// Render hitboxes
	// for (int i = 0; i < objects.size(); i++) {
	// 	Object* object1 = objects[i];
	// 	renderHitbox(renderer, camPos, *object1);
	// }

	// Render HUD
	std::string msg = "Vida: ";
	msg += std::to_string(player->getHealth());
	msg += "/100";
	atlas.render(msg, 4, 8);

	msg = "Pontos: ";
	msg += std::to_string(player->getScore());
	atlas.render(msg, 4, 18);

	SDL_RenderPresent(renderer);
}

}  // namespace Game