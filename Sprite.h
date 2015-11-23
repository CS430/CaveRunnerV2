#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <GL\glew.h>
class Sprite
{
public:
	Sprite(float initX, float initY, float initWidth, float initHeight);
	~Sprite();

	void init();

	void update();
	void render();

	void setX(float newX);
	void setY(float newY);

private:

	float x;
	float y;
	float width;
	float height;

	GLuint vboID;

};

#endif

