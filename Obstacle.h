#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"

class Obstacle : public Entity {
public:
	Obstacle(float xPos, float yPos, float width, float height, std::string texturePath);
	~Obstacle();

	void update();
	void render();
private:
};

#endif