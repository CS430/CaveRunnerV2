#include "PlayState.h"
#include "Keys.h"
#include "Obstacle.h"

#include <cmath>

std::vector<Obstacle*> obstacles;

PlayState::PlayState(StateManager* sm) : stateManager(sm) {
	glClearColor(0.153f, 0.051f, 0.0f, 0.0f);

	obstacles = { 
		new Obstacle(-0.5f, -0.6f, 0.05f, 0.1f, playTextureFilePath),
		new Obstacle(-0.75f, -0.1f, 0.05f, 0.1f, playTextureFilePath),
		new Obstacle(0.5f, 0.4f, 0.05f, 0.1f, playTextureFilePath)
	};

	player = new Player(0.0f, 0.0f, 0.05f, 0.1f, playTextureFilePath);
}

PlayState::~PlayState() {

}

void PlayState::init() {
	shader.compileShaders("PlayVertShader.glsl", "PlayFragShader.glsl");
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

	for (Obstacle* obstacle : obstacles) {
		if (player->getBottomBound() <= obstacle->getTopBound()
			&& player->getTopBound() >= obstacle->getBottomBound()
			&& player->getLeftBound() <= obstacle->getRightBound()
			&& player->getRightBound() >= obstacle->getLeftBound()) {
			float rightDist = std::abs(player->getLeftBound() - obstacle->getRightBound());
			float topDist = std::abs(player->getBottomBound() - obstacle->getTopBound());
			float leftDist = std::abs(player->getRightBound() - obstacle->getLeftBound());
			float bottomDist = std::abs(player->getTopBound() - obstacle->getBottomBound());

			if (rightDist < topDist && rightDist < leftDist && rightDist < bottomDist) {
				player->setXPosition(obstacle->getRightBound() + player->getWidth());
				player->setXAccel(0.0f);
			}
			else if (topDist < rightDist && topDist < leftDist && topDist < bottomDist) {
				player->setHasJumped(false);
				player->setHasDoubleJumped(false);

				player->setYPosition(obstacle->getTopBound() + player->getHeight());
				player->setYAccel(0.0f);
			}
			else if (leftDist < topDist && leftDist < rightDist && leftDist < bottomDist) {
				player->setXPosition(obstacle->getLeftBound() - player->getWidth());
				player->setXAccel(0.0f);
			}
			else if (bottomDist < topDist && bottomDist < leftDist && bottomDist < rightDist) {
				player->setYPosition(obstacle->getBottomBound() - player->getHeight());
				player->setYAccel(0.0f);
			}
		}

		obstacle->update();
		obstacle->render();
	}

	shader.unuse();
}

void PlayState::handleInput() {
	if (Keys::isDown(Keys::S)) {
		player->setIsCrouching(true);
	} else {
		player->setTexture(player->getIsFacingRight() ? player->idleRight : player->idleLeft);
		player->setIsCrouching(false);

		if (Keys::isPressed(Keys::ESC)) {
			stateManager->loadState(StateManager::PAUSED);
		}

		if (Keys::isDown(Keys::D)) {
			if (!player->getIsCrouching() && player->getXAccel() < player->maxPlayerSpeed) {
				player->setXAccel(player->getXAccel() + player->playerAcccel);
				player->setTexture(player->runRight);
				player->setIsFacingRight(true);
			}
		}

		if (Keys::isDown(Keys::A)) {
			if (!player->getIsCrouching() && player->getXAccel() > -player->maxPlayerSpeed) {
				player->setXAccel(player->getXAccel() - player->playerAcccel);
				player->setTexture(player->runLeft);
				player->setIsFacingRight(false);
			}
		}

		if (Keys::isPressed(Keys::W) && !player->getIsCrouching()) {
			if (!player->getHasJumped()) {
				player->setYAccel(player->jumpAccel);
				player->setHasJumped(true);
			} else if (!player->getHasDoubleJumped()) {
				player->setYAccel(player->jumpAccel);
				player->setHasDoubleJumped(true);
			}
		}
	}
}