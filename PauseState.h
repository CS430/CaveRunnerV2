#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "State.h"

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