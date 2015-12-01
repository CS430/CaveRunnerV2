#ifndef EXIT_H
#define EXIT_H

#include "Entity.h"

class Exit : public Entity {
public:
	Exit(float startX, float startY, float startW, float startH, std::string filePath);
	~Exit();

	void update();
	void render();

private:
};

#endif