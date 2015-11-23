#include "Background.h"


Background::Background(float startX, float startY, float startW, float startH, std::string filePathToTexture) : Entity(startX, startY, startH, startW, filePathToTexture)
{
	objSprite.init();
}


Background::~Background()
{

}

void Background::update()
{

}

void Background::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objTexture.id);

	objSprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}