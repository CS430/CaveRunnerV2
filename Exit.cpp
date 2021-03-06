#include "Exit.h"

Exit::Exit(float xPos, float yPos, float width, float height, GLTexture texture) : Entity(xPos, yPos, width, height, texture) {
	objSprite.init();

	objSprite.setX(xPos);
	objSprite.setY(yPos);
	objSprite.setW(width);
	objSprite.setH(height);
}

Exit::~Exit() {

}

void Exit::update() {

}

void Exit::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objTexture.id);

	objSprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}