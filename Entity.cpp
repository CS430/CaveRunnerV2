#include "Entity.h"
#include "ImageLoader.h"



Entity::Entity(float startX, float startY, float startW, float startH, std::string filePathToTexture) : x(startX), y(startY), width(startW), height(startH), textureFilePath(filePathToTexture), objSprite(x, y, width, height)
{
	objTexture = ImageLoader::loadPNG(textureFilePath);
}

Entity::~Entity()
{

}



/*------------------------------------------------------*/
//Getters
/*------------------------------------------------------*/
float Entity::getXPosition()
{
	return x;
}



float Entity::getYPosition()
{
	return y;
}



bool Entity::isMoving()
{
	return moving;
}



bool Entity::isUP()
{
	return up;
}



bool Entity::isDown()
{
	return down;
}



bool Entity::isLeft()
{
	return left;
}



bool Entity::isRight()
{
	return right;
}


/*------------------------------------------------------*/
//Setters
/*------------------------------------------------------*/
void Entity::setMoving(bool b)
{
	moving = b;
}

void Entity::setUP(bool b)
{
	up = b;
}

void Entity::setDown(bool b)
{
	down = b;
}

void Entity::setLeft(bool b)
{
	left = b;
}

void Entity::setRight(bool b)
{
	right = b;
}


void Entity::setPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}