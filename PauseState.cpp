#include "PauseState.h"
#include "Keys.h"

PauseState::PauseState(StateManager* sm) : stateManager(sm) {

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