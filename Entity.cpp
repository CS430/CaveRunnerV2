#include "Entity.h"
#include "ImageLoader.h"

Entity::Entity(float startX, float startY, float startW, float startH, std::string filePathToTexture) : x(startX), y(startY), width(startW), height(startH), textureFilePath(filePathToTexture), objSprite(x, y, width, height) {
	objTexture = ImageLoader::loadPNG(textureFilePath);
	xAccel = 0.0f;
	yAccel = 0.0f;
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
	xAccel = x;
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

float Entity::getWidth() {
	return width;
}

void Entity::setHasColidedX(bool hasColided) {
	hasColidedX = hasColided;
}

bool Entity::getHasColidedX() {
	return hasColidedX;
}

void Entity::setHasColidedY(bool hasColided) {
	hasColidedY = hasColided;
}

bool Entity::getHasColidedY() {
	return hasColidedY;
}

float Entity::getTopBound() {
	return y + height;
}

float Entity::getRightBound() {
	return x + width;
}

float Entity::getBottomBound() {
	return y - height;
}

float Entity::getLeftBound() {
	return x - width;
}