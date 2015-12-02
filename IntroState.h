#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "State.h"
#include "GLSLProgram.h"
#include "Background.h"
#include "ImageLoader.h"

class IntroState : public State {
public:
	IntroState(StateManager* sm);
	~IntroState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	//vaues used for determining the alpha value
	int tick;
	float alpha;
	int target;

	//filepath to our image resource
	const GLTexture backgroundTex = ImageLoader::loadPNG("Resources/Images/caverunnersplash.png");

	StateManager* stateManager;

	GLSLProgram shader;

	Background background;
};

#endif