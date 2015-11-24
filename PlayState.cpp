#include "PlayState.h"
#include "Keys.h"

PlayState::PlayState(StateManager* sm) : stateManager(sm) {
	glClearColor(0.153f, 0.051f, 0.0f, 0.0f);

	player = new Player(0.0f, 0.0f, 0.02f, 0.06f, playTextureFilePath);
}

PlayState::~PlayState() {

}

void PlayState::init() {
	shader.compileShaders("MenuVertShader.glsl", "MenuFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();
}

void PlayState::update() {
	handleInput();
}

void PlayState::render() {
	glBegin(GL_TRIANGLES);
		player->update();
	glEnd();
}

void PlayState::handleInput() {
	if (Keys::isDown(Keys::S)) {
		player->setIsCrouching(true);
	}

	if (Keys::isPressed(Keys::ESC)) {
		stateManager->loadState(StateManager::PAUSED);
	}

	if (Keys::isDown(Keys::D)) {
		if (!player->getIsCrouching() && player->getXAccel() < player->maxPlayerSpeed) {
			player->setXAccel(player->playerAcccel);
		}
	}

	if (Keys::isDown(Keys::A)) {
		if (!player->getIsCrouching() && player->getXAccel() > -player->maxPlayerSpeed) {
			player->setXAccel(-player->playerAcccel);
		}
	}

	if (Keys::isPressed(Keys::W)) {
		if (!player->getIsCrouching()) {
			if (player->getYPos() - player->getHeight() <= -1.0f) {
				player->setYAccel(player->jumpAccel);
			} else if (!player->getHasDoubleJumped()) {
				player->setYAccel(player->jumpAccel);
				player->setHasDoubleJumped(true);
			}
		}
	}
}