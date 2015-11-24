#include "Player.h"
#include <vector>

std::vector<std::vector<float>> vertices;

Player::Player(float xPos, float yPos, float startW, float startH, std::string filePathToTexture) : Entity(xPos, yPos, startW, startH, filePathToTexture) {
	xAccel = 0.0f;
	yAccel = 0.0f;

	vertices = {
		{ xPos - width, yPos - height },
		{ xPos - width, yPos + height },
		{ xPos + width, yPos - height },
		{ xPos - width, yPos + height },
		{ xPos + width, yPos + height },
		{ xPos + width, yPos - height }
	};
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

std::vector<std::vector<float>> Player::getVertices() {
	return vertices;
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
	yAccel -= gravity;
	y += yAccel;

	if (xAccel > 0.0f) {
		xAccel -= friction;
	} else if (xAccel < 0.0f) {
		xAccel += friction;
	} else {
		xAccel = 0;
	}

	x += xAccel;

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

	vertices = {
		{ x - width, y - height },
		{ x - width, y + height },
		{ x + width, y - height },
		{ x - width, y + height },
		{ x + width, y + height },
		{ x + width, y - height }
	};

	for (int i = 0; i < vertices.size(); i++) {
		glTexCoord2f(0.5f, 0.5f);
		glVertex2f(vertices[i][0], vertices[i][1]);
	}

	if (isCrouching) {
		height = height + width;
		width = height - width;
		height = height - width;

		setIsCrouching(false);
	}
}

void Player::render() {
	//fill buffer with new player position as a 
}