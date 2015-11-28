#include "Obstacle.h"

Obstacle::Obstacle(float xPos, float yPos, float width, float height, std::string texturePath) : Entity(xPos, yPos, width, height, texturePath) {
	objSprite.init();

	objSprite.setX(xPos);
	objSprite.setY(yPos);
	objSprite.setW(width);
	objSprite.setH(height);
}

Obstacle::~Obstacle() {

}

void Obstacle::update() {
	objSprite.update();
}

void Obstacle::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objTexture.id);

	objSprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}