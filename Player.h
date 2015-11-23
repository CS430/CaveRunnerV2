#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Player();

	void update();
	void render();

	bool checkValidMove();
	
};

#endif

