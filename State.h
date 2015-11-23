#include "StateManager.h"

#ifndef STATE_H
#define STATE_H

class State {
public:
	virtual void init() = 0;		//initilize the state
	virtual void update() = 0;		//update the game logic based off of which state is currently active
	virtual void render() = 0;		//draw the required objects for the current state.
	virtual void handleInput() = 0; //used to deal with input. in the GameScreen class we will use glfwPollEvents to set 
									//the state of different key presses in our key class. we will then check the key class
									//in this function to determin if a key we use in a particular state is pressed \.
protected:
	StateManager stateManager;
};

#endif