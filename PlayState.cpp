#include "PlayState.h"
#include "Keys.h"

PlayState::PlayState(StateManager* sm) : stateManager(sm) {
	glClearColor(0.153f, 0.051f, 0.0f, 0.0f);

	player = new Player(0.0f, 0.0f, 0.04f, 0.08f, playTextureFilePath);
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
	shader.use();

	GLint textureLocation = shader.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint selectedLocation = shader.getUniformLocation("selected");
	glUniform1i(selectedLocation, true);

		player->update();

	player->render();

	shader.unuse();
}

void PlayState::handleInput() {
	if (Keys::isDown(Keys::S)) {
		player->setIsCrouching(true);
	} else {
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

		if (Keys::isPressed(Keys::W) && !player->getIsCrouching()) {
			if (player->getYPos() - player->getHeight() <= -1.0f) {
				player->setYAccel(player->jumpAccel);
			} else if (!player->getHasDoubleJumped()) {
				player->setYAccel(player->jumpAccel);
				player->setHasDoubleJumped(true);
			}
		}
	}
}