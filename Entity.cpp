#include "Entity.h"
#include "ImageLoader.h"

Entity::Entity(float startX, float startY, float startW, float startH, std::string filePathToTexture) : x(startX), y(startY), width(startW), height(startH), textureFilePath(filePathToTexture), objSprite(x, y, width, height) {
	objTexture = ImageLoader::loadPNG(textureFilePath);
}

Entity::~Entity() {

}

void Entity::setXPosition(float newX) {
	x = newX;
}

float Entity::getXPosition() {
	return x;
}

void Entity::setYPosition(float newY) {
	y = newY;
}

float Entity::getYPosition() {
	return y;
}

void Entity::setPosition(float newX, float newY) {
	x = newX;
	y = newY;
}

void Entity::setTexture(GLTexture &texture) {
	objTexture = texture;
}

float Entity::getXAccel() {
	return xAccel;
}

void Entity::setXAccel(float x) {
	xAccel += x;
}

float Entity::getYAccel() {
	return yAccel;
}

void Entity::setYAccel(float y) {
	yAccel = y;
}

float Entity::getHeight() {
	return height;
}