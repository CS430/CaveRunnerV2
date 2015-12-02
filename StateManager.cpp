#include "StateManager.h"
#include "IntroState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"

#include <iostream>

StateManager::StateManager() : previousState(-1), currentState(-1), gameStates(3) {

}

StateManager::~StateManager() {

}

void StateManager::init() {
	loadState(StateManager::INTRO);
}

void StateManager::loadState(int state) {
	previousState = currentState;
	currentState = state;
	unloadState(previousState);

	switch (state) {
	case INTRO:
		gameStates[state] = new IntroState(this);
		break;

	case MAINMENU:
		gameStates[state] = new MainMenuState(this);
		break;

	case PLAY:
		gameStates[state] = new PlayState(this);
		break;
	}

	gameStates[currentState]->init();
}

void StateManager::unloadState(int state) {
	if (!previousState == -1) {
		delete gameStates[state];
	}
}

void StateManager::update() {
	gameStates[currentState]->update();
}

void StateManager::render() {
	gameStates[currentState]->render();
}