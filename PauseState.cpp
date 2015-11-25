#include "PauseState.h"
#include "Keys.h"

#include "GL\glew.h"

PauseState::PauseState(StateManager* sm) : stateManager(sm) {
	glClearColor(0.0765f, 0.0255f, 0.0f, 0.0f);
}

PauseState::~PauseState() {

}

void PauseState::init() {

}

void PauseState::update() {
	handleInput();
}

void PauseState::render() {

}

void PauseState::handleInput() {
	if (Keys::isPressed(Keys::ESC)) {
		stateManager->loadState(StateManager::MAINMENU);
	} else if (Keys::isPressed(Keys::ENTER)) {
		stateManager->loadState(StateManager::PLAY);
	}
}