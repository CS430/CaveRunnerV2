#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Player.h"
#include "Exit.h"
#include "GLTexture.h"
#include "GLSLProgram.h"
#include "Obstacle.h"
#include "Background.h"
#include "ImageLoader.h"

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

	const GLTexture playerStartTex = ImageLoader::loadPNG("Resources/Images/player_idle_right.png");
	const GLTexture obstacleTex = ImageLoader::loadPNG("Resources/Images/untextured_block.png");
	const GLTexture exitTex = ImageLoader::loadPNG("Resources/Images/exit.png");
	const GLTexture backgroundTex = ImageLoader::loadPNG("Resources/Images/cave_background.png");

	GLTexture playerTexture;

	GLSLProgram shader;

	Background background;
};

#endif