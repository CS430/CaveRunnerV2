#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>

class Player : public Entity {
public:
	Player(float startX, float startY, float startW, float startH, GLTexture texture);
	~Player();

	const float gravity = 0.00075f;
	const float friction = 0.0005f;
	const float playerAcccel = 0.00085f;
	const float maxPlayerSpeed = 0.020f;
	const float jumpAccel = 0.02f;
	const float airResistance = 0.45f;

	void update();
	void render();

	void jump();
	void goLeft();
	void goRight();

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

	bool getIsWallSlidingLeft();
	void setIsWallSlidingLeft(bool r);

	bool getIsWallSlidingRight();
	void setIsWallSlidingRight(bool r);

	bool getIsDead();
	void setIsDead(bool d);

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
	GLTexture standingSlideRight;
	GLTexture standingSlideLeft;
	GLTexture wallSlidingLeft;
	GLTexture wallSlidingRight;
	
private:
	bool isCrouching;
	bool wasCrouching;
	bool hasJumped;
	bool hasDoubleJumped;
	bool isFacingRight;
	bool isDead;
	bool isWallSlidingLeft;
	bool isWallSlidingRight;

	void switchHeightAndWidth();
};

#endif