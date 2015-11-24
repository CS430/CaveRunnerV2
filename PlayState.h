#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Player.h"
#include "GLTexture.h"
#include "GLSLProgram.h"

class PlayState : public State {
public:
	PlayState(StateManager* sm);
	~PlayState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	StateManager* stateManager;

	Player* player;

	//File paths to our Image Resources
	const std::string& playTextureFilePath = "Resources/Images/play.png";

	//Player player;
	GLTexture playerTexture;

	//our shader program
	GLSLProgram shader;
};

#endif