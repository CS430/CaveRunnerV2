#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>

class State;
class StateManager {
public:
	const static int INTRO  = 0;
	const static int MAINMENU = 1;
	const static int PLAY = 2;

	StateManager();
	~StateManager();

	void loadState(int state);
	void unloadState(int state);

	void init();

	//called by the gamescreen class in the main game loop;
	void update();

	//called by the gamescreen class in the main game loop;
	void render();

private:
	const static int NUM_OF_STATES = 3;

	int currentState;
	int previousState;

	std::vector<State*> gameStates;
};

#endif