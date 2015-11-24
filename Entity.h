#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Sprite.h"
#include "GLTexture.h"

class Entity {
public:
	Entity(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Entity();

	virtual void update() =  0;
	virtual void render() = 0;

	//virtual bool checkValidMove();

	virtual void setPosition(float newX, float newY);

	virtual float getXPosition();
	virtual float getYPosition();

protected:
	float x;
	float y;

	float width;
	float height;

	Sprite objSprite;
	GLTexture objTexture;
	std::string textureFilePath;
};

#endif