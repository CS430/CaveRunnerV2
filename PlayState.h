#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Player.h"
#include "Exit.h"
#include "GLTexture.h"
#include "GLSLProgram.h"

class PlayState : public State {
public:
	PlayState(StateManager *sm);
	~PlayState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	StateManager *stateManager;
	Player *player;
	Exit *exit;

	//File paths to our Image Resources
	const std::string& playerTexFilePath = "Resources/Images/player_idle_right.png";
	const std::string& obstacleTexFilePath = "Resources/Images/untextured_block.png";
	const std::string& exitTexFilePath = "Resources/Images/exit.png";

	//Player player;
	GLTexture playerTexture;

	//our shader program
	GLSLProgram shader;
};

#endif