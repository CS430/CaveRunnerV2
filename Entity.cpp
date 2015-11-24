#include "Entity.h"
#include "ImageLoader.h"

Entity::Entity(float startX, float startY, float startW, float startH, std::string filePathToTexture) : x(startX), y(startY), width(startW), height(startH), textureFilePath(filePathToTexture), objSprite(x, y, width, height) {
	objTexture = ImageLoader::loadPNG(textureFilePath);
}

Entity::~Entity() {

}

float Entity::getXPosition() {
	return x;
}

float Entity::getYPosition() {
	return y;
}

void Entity::setPosition(float newX, float newY) {
	x = newX;
	y = newY;
}