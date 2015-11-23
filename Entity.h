#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Sprite.h"
#include "GLTexture.h"


class Entity
{
public:

//	Entity();
	Entity(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Entity();

	virtual void update() =  0;
	virtual void render() = 0;

	//virtual bool checkValidMove();

	virtual void setPosition(float newX, float newY);

	virtual float getXPosition();
	virtual float getYPosition();

	virtual void setMoving(bool b);
	virtual void setUP(bool b);
	virtual void setDown(bool b);
	virtual void setLeft(bool b);
	virtual void setRight(bool b);

	virtual bool isMoving();
	virtual bool isUP();
	virtual bool isDown();
	virtual bool isLeft();
	virtual bool isRight();



protected:

	float x;
	float y;

	float width;
	float height;

	bool moving;
	bool jumping;
	bool left;
	bool right;
	bool up;
	bool down;

	Sprite objSprite;
	GLTexture objTexture;
	std::string textureFilePath;
};

#endif