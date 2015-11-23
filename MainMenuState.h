#include "State.h"
#include "GLSLProgram.h"
#include "Label.h"
//#include "Sprite.h"
//#include "GLTexture.h"

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

class MainMenuState : public State {
public:
	MainMenuState(StateManager* sm);
	~MainMenuState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	//values for selecting a label
	const int maxIndex = 1;
	int index;

	//File paths to our Image Resources
	const std::string& playTextureFilePath = "Resources/Images/play.png";
	const std::string& quitTextureFilePath = "Resources/Images/quit.png";

	//State manager
	StateManager* stateManager;

	//our shader program
	GLSLProgram shader;
	
	//our entities
	std::vector<Label*> labels;
};

#endif