#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Sprite.h"
#include "GLTexture.h"

class Entity {
public:
	Entity(float startX, float startY, float startW, float startH, GLTexture texture);
	~Entity();

	virtual void update() =  0;
	virtual void render() = 0;

	virtual void setPosition(float newX, float newY);

	virtual float getXPosition();
	virtual void setXPosition(float x);

	virtual float getYPosition();
	virtual void setYPosition(float y);

	virtual float getXAccel();
	virtual void setXAccel(float x);

	virtual float getYAccel();
	virtual void setYAccel(float y);

	virtual float getHeight();

	virtual float getWidth();

	virtual float getTopBound();
	virtual float getRightBound();
	virtual float getBottomBound();
	virtual float getLeftBound();

	virtual void setHasColidedX(bool hasColided);
	virtual bool getHasColidedX();

	virtual void setHasColidedY(bool hasColided);
	virtual bool getHasColidedY();

	virtual void setTexture(GLTexture &texture);

protected:
	float x;
	float y;
	float xAccel = 0;
	float yAccel = 0;
	float width;
	float height;

	bool hasColidedX = false;
	bool hasColidedY = false;

	Sprite objSprite;
	GLTexture objTexture;
};

#endif