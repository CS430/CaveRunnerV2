#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>

class Player : public Entity {
public:
	Player(float startX, float startY, float startW, float startH, std::string filePath);
	~Player();

	const float gravity = 0.00075f;
	const float friction = 0.0004f;
	const float playerAcccel = 0.0008f;
	const float maxPlayerSpeed = 0.025f;
	const float jumpAccel = 0.02f;

	void update();
	void render();

	void setHasJumped(bool j);
	bool getHasJumped();
	
	void setHasDoubleJumped(bool j);
	bool getHasDoubleJumped();

	void setIsCrouching(bool c);
	bool getIsCrouching();

	void setWasCrouching(bool c);
	bool getWasCrouching();

	bool getIsFacingRight();
	void setIsFacingRight(bool r);

	GLTexture slideRight;
	GLTexture slideLeft;
	GLTexture runRight;
	GLTexture runLeft;
	GLTexture idleRight;
	GLTexture idleLeft;
	GLTexture jumpRight;
	GLTexture jumpLeft;
	GLTexture fallRight;
	GLTexture fallLeft;
	
private:
	bool isCrouching;
	bool wasCrouching;
	bool hasJumped;
	bool hasDoubleJumped;
	bool isFacingRight;
};

#endif