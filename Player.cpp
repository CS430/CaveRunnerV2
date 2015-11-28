#include "Player.h"
#include "ImageLoader.h"

#include <vector>

#include <GLFW\glfw3.h>

Player::Player(float xPos, float yPos, float startW, float startH, std::string filePath) : Entity(xPos, yPos, startW, startH, filePath) {
	objSprite.init();

	slideRight = ImageLoader::loadPNG("Resources/Images/player_slide_right.png");
	slideLeft = ImageLoader::loadPNG("Resources/Images/player_slide_left.png");
	runRight = ImageLoader::loadPNG("Resources/Images/player_run_1_right.png");
	runLeft = ImageLoader::loadPNG("Resources/Images/player_run_1_left.png");
	idleRight = ImageLoader::loadPNG("Resources/Images/player_idle_right.png");
	idleLeft = ImageLoader::loadPNG("Resources/Images/player_idle_left.png");
	jumpRight = ImageLoader::loadPNG("Resources/Images/player_jump_1_right.png");
	jumpLeft = ImageLoader::loadPNG("Resources/Images/player_jump_1_left.png");
	fallRight = ImageLoader::loadPNG("Resources/Images/player_fall_1_right.png");
	fallLeft = ImageLoader::loadPNG("Resources/Images/player_fall_1_left.png");
}

Player::~Player() {

}

void Player::setHasJumped(bool j) {
	hasJumped = j;
}

bool Player::getHasJumped() {
	return hasJumped;
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

void Player::update() {
	if (yAccel > 0.0f) {
		setTexture(isFacingRight ? jumpRight : jumpLeft);
		hasJumped = true;
	} else if (yAccel < 0.0f) {
		setTexture(isFacingRight ? fallRight : fallLeft);
		hasJumped = true;
	}

	if (xAccel >= playerAcccel) {
		xAccel -= friction;
	} else if (xAccel <= -playerAcccel) {
		xAccel += friction;
	} else {
		xAccel = 0.0f;
	}

	if (isCrouching) {
		setTexture(isFacingRight ? slideRight : slideLeft);

		if (!wasCrouching) {
			height = height + width;
			width = height - width;
			height = height - width;

			wasCrouching = true;
		}
	}

	objSprite.setY(y += yAccel -= gravity);

	if (y - height <= -1.0f) {
		y = -1.0f + height;

		yAccel = 0.0f;
		hasJumped = false;
		hasDoubleJumped = false;
	}

	objSprite.setX(x += xAccel);

	objSprite.setH(height);
	objSprite.update();
	objSprite.setW(width);

	if (wasCrouching && !isCrouching) {
		height = height + width;
		width = height - width;
		height = height - width;

		wasCrouching = false;
	}
}

void Player::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objTexture.id);

	objSprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Player::getIsFacingRight() {
	return isFacingRight;
}

void Player::setIsFacingRight(bool isRight) {
	isFacingRight = isRight;
}

bool Player::getWasCrouching() {
	return wasCrouching;
}

void Player::setWasCrouching(bool crouching) {
	wasCrouching = crouching;
}