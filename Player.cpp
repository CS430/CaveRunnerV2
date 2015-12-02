#include "Player.h"
#include "ImageLoader.h"

#include <vector>

#include <GLFW\glfw3.h>

Player::Player(float xPos, float yPos, float startW, float startH, GLTexture texture) : Entity(xPos, yPos, startW, startH, texture) {
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
	standingSlideRight = ImageLoader::loadPNG("Resources/Images/player_standing_slide_right.png");
	standingSlideLeft = ImageLoader::loadPNG("Resources/Images/player_standing_slide_left.png");
}

Player::~Player() {

}

void Player::jump() {
	if (!isCrouching) {
		if (!hasJumped) {
			yAccel = jumpAccel;
			hasJumped = true;
		}
		else if (!hasDoubleJumped) {
			yAccel = jumpAccel;
			hasDoubleJumped = true;
		}
	}
}

void Player::goLeft() {
	if (xAccel < maxPlayerSpeed / 2) {
		if (!isCrouching && xAccel > -maxPlayerSpeed) {
			float accel = !hasJumped ? playerAcccel : (playerAcccel * airResistance);

			xAccel -= accel;
		}

		objTexture = runLeft;
		isFacingRight = false;
	}
}

void Player::goRight() {
	if (xAccel > -maxPlayerSpeed / 2) {
		if (!isCrouching && xAccel < maxPlayerSpeed) {
			float accel = !hasJumped ? playerAcccel : (playerAcccel * airResistance);

			xAccel += accel;
		}

		objTexture = runRight;
		isFacingRight = true;
	}
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
	}
	else if (yAccel < 0.0f) {
		setTexture(isFacingRight ? fallRight : fallLeft);
		hasJumped = true;
	}

	if (xAccel >= playerAcccel * airResistance) {
		float tempFriction = !hasJumped ? friction : friction * airResistance;

		xAccel = (xAccel - tempFriction < 0.0f ? 0.0f : xAccel - tempFriction);
	}
	else if (xAccel <= -playerAcccel * airResistance) {
		float tempFriction = !hasJumped ? friction : friction * airResistance;

		xAccel = (xAccel + tempFriction > 0.0f ? 0.0f : xAccel + tempFriction);
	}
	else {
		xAccel = 0.0f;
	}

	if (isCrouching) {
		setTexture(isFacingRight ? slideRight : slideLeft);

		if (!wasCrouching) {
			switchHeightAndWidth();

			wasCrouching = true;
		}
	}

	if (y + height <= -1.0f) {
		yAccel = 0.0f;

		isDead = true;
	}

	objSprite.setPhysicalAttributes(x += xAccel, y += yAccel -= gravity, width, height);

	if (wasCrouching && !isCrouching) {
		switchHeightAndWidth();

		wasCrouching = false;
	}
}

void Player::switchHeightAndWidth() {
	height = height + width;
	width = height - width;
	height = height - width;
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

bool Player::getIsDead() {
	return isDead;
}

void Player::setIsDead(bool dead) {
	isDead = dead;
}