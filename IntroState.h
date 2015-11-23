#pragma once

#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "State.h"
#include "GLSLProgram.h"
#include "Background.h"


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
	const std::string backgroundFilePath = "Resources/Images/caverunnersplash.png";
	
	//State Manager
	StateManager* stateManager;

	//our shader program 
	GLSLProgram shader;

	//our entity
	Background background;


};

#endif