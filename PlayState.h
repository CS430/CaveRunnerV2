#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Player.h"
#include "Exit.h"
#include "GLTexture.h"
#include "GLSLProgram.h"
#include "Obstacle.h"
#include "Background.h"

class PlayState : public State {
public:
	PlayState(StateManager *sm);
	~PlayState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	std::vector<Obstacle*> obstacles;
	StateManager *stateManager;
	Player *player;
	Exit *exit;

	const std::string& playerTexFilePath = "Resources/Images/player_idle_right.png";
	const std::string& obstacleTexFilePath = "Resources/Images/untextured_block.png";
	const std::string& exitTexFilePath = "Resources/Images/exit.png";
	const std::string backgroundFilePath = "Resources/Images/cave_background.png";

	GLTexture playerTexture;

	GLSLProgram shader;

	Background background;
};

#endif