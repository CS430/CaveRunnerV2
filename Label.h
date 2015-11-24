#ifndef LABEL_H
#define LABEL_H

#include "Entity.h"
#include <string>

class Label : public Entity {
public:
	//float startX, float startY, float startW, float startH, std::string filePathToTexture
	Label(float startX, float startY, float startW, float startH, std::string filePathToTexture);
	~Label();

	void update();
	void render();

	int isSelected();
	void setSelected(int state);

private:
	std::string textureFilePath;
	int selected;					//int boolean 0 == false 1== true because opengl does not have a uniform bool value
};

#endif