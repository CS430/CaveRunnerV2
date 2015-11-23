#include "Player.h"


Player::Player(float startX, float startY, float startW, float startH, std::string filePathToTexture) : Entity(startX,startY, startW, startH, filePathToTexture)
{
}


Player::~Player()
{
}


void Player::update()
{
	//update player logic here
}

void Player::render()
{
	//fill buffer with new player position as a 
}


