#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity {
public:
	Background(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Background();

	void update();
	void render();
};

#endif