#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
#include <string>

class Player : public Entity {
public:
	Player(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Player();

	const float gravity = 0.000003f;
	const float friction = 0.0000005f;
	const float playerAcccel = 0.000001f;
	const float maxPlayerSpeed = 0.00075f;
	const float jumpAccel = 0.0015f;

	void update();
	void render();

	bool checkValidMove();

	void init();
	float getXPos();
	float getYPos();
	float getXAccel();
	float getHeight();
	std::vector<std::vector<float>> getVertices();
	void setXPos(float x);
	void setXAccel(float x);
	void setYPos(float y);
	void setYAccel(float y);
	void setHasDoubleJumped(bool j);
	bool getHasDoubleJumped();
	void setIsCrouching(bool c);
	bool getIsCrouching();
	
private:
	float xAccel;
	float yAccel;
	bool isCrouching;
	bool hasDoubleJumped;
};

#endif