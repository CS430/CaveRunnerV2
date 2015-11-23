#pragma once
#include "Entity.h"
class Background :
	public Entity
{
public:
	Background(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Background();

	void update();
	void render();
};

