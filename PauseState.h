#include "State.h"

#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

class PauseState : public State {
public:
	PauseState(StateManager* sm);
	~PauseState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	StateManager* stateManager;
};

#endif