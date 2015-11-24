#include "Player.h"

#include <vector>

#include <GLFW\glfw3.h>

Player::Player(float xPos, float yPos, float startW, float startH, std::string imgPath) : Entity(xPos, yPos, startW, startH, imgPath) {
	objSprite.init();
	xAccel = 0.0f;
	yAccel = 0.0f;
}

Player::~Player() {

}

void Player::setXAccel(float x) {
	xAccel += x;
}

float Player::getXAccel() {
	return xAccel;
}

float Player::getXPos() {
	return x;
}

float Player::getYPos() {
	return y;
}

void Player::setYAccel(float y) {
	yAccel = y;
}

void Player::setHasDoubleJumped(bool j) {
	hasDoubleJumped = j;
}

bool Player::getHasDoubleJumped() {
	return hasDoubleJumped;
}

void Player::setIsCrouching(bool c) {
	isCrouching = c;
}

bool Player::getIsCrouching() {
	return isCrouching;
}

float Player::getHeight() {
	return height;
}

void Player::update() {
	objSprite.setY(y += yAccel -= gravity);

	if (xAccel >= playerAcccel) {
		xAccel -= friction;
	} else if (xAccel <= -playerAcccel) {
		xAccel += friction;
	} else {
		xAccel = 0.0f;
	}

	objSprite.setX(x += xAccel);

	if (isCrouching) {
		height = height + width;
		width = height - width;
		height = height - width;
	}

	if (y - height <= -1.0f) {
		y = -1.0f + height;
		yAccel = 0.0f;

		hasDoubleJumped = false;
	}

	objSprite.setH(height);
	objSprite.update();
	objSprite.setW(width);

	if (isCrouching) {
		height = height + width;
		width = height - width;
		height = height - width;

		setIsCrouching(false);
	}
}

void Player::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objTexture.id);

	objSprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}