#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"

class Obstacle : public Entity {
public:
	Obstacle(float xPos, float yPos, float width, float height, GLTexture texture);
	~Obstacle();

	void update();
	void render();

private:
};

#endif