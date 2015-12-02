#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "GLSLProgram.h"
#include "Label.h"
#include "ImageLoader.h"

class MainMenuState : public State {
public:
	MainMenuState(StateManager* sm);
	~MainMenuState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	const int maxIndex = 1;
	int index;

	const GLTexture playTex = ImageLoader::loadPNG("Resources/Images/play.png");
	const GLTexture quitTex = ImageLoader::loadPNG("Resources/Images/quit.png");

	StateManager* stateManager;

	GLSLProgram shader;

	std::vector<Label*> labels;
};

#endif