#ifndef SPRITE_H
#define SPRITE_H

#include "Vertex.h"

#include <GL\glew.h>
#include <vector>

class Sprite {
public:
	Sprite(float initX, float initY, float initWidth, float initHeight);
	~Sprite();

	void init();

	void update();
	void render();

	void setX(float newX);
	void setY(float newY);
	void setH(float newH);
	void setW(float newW);

	void setPhysicalAttributes(float x, float y, float width, float height);

private:
	float x;
	float y;
	float width;
	float height;

	std::vector<Position> vertexPosition;

	GLuint vboID;
};

#endif