#include "PlayState.h"
#include "Keys.h"
#include "Obstacle.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

std::vector<Obstacle*> obstacles;

GLint playTextureLocation;
GLint matrixId;

PlayState::PlayState(StateManager* sm) : stateManager(sm) {
	glClearColor(0.153f, 0.051f, 0.0f, 0.0f);

	obstacles = { 
		new Obstacle(-0.5f, -0.6f, 0.05f, 0.1f, obstacleTexFilePath),
		new Obstacle(-0.75f, -0.1f, 0.05f, 0.1f, obstacleTexFilePath),
		new Obstacle(0.55f, 0.4f, 0.1f, 0.1f, obstacleTexFilePath),
		new Obstacle(0.5f, 0.75f, 0.05f, 0.1f, obstacleTexFilePath),
		new Obstacle(0.0f, -1.0f, 0.05f, 0.1f, obstacleTexFilePath)
	};

	player = new Player(0.0f, 0.0f, 0.04f, 0.08f, playerTexFilePath);
}

PlayState::~PlayState() {

}

void PlayState::init() {
	shader.compileShaders("PlayVertShader.glsl", "PlayFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();

	playTextureLocation = shader.getUniformLocation("mySampler");
	matrixId = shader.getUniformLocation("MVP");
}

void PlayState::update() {
	handleInput();
}

void PlayState::render() {
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(3.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(3, 3, -3), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	Model = Model * glm::mat4(player->getXPosition(), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, player->getXPosition(), 0, 0, 1);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	shader.use();

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(playTextureLocation, 0);

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
				player->setXAccel(player->getXAccel() < 0 ? 0.0f : player->getXAccel());
			} else if (topDist < rightDist && topDist < leftDist && topDist < bottomDist) {
				player->setHasJumped(false);
				player->setHasDoubleJumped(false);

				player->setYPosition(obstacle->getTopBound() + player->getHeight());
				player->setYAccel(player->getYAccel() < 0 ? 0.0f : player->getYAccel());
			} else if (leftDist < topDist && leftDist < rightDist && leftDist < bottomDist) {
				player->setXPosition(obstacle->getLeftBound() - player->getWidth());
				player->setXAccel(player->getXAccel() > 0 ? 0.0f : player->getXAccel());
			} else if (bottomDist < topDist && bottomDist < leftDist && bottomDist < rightDist) {
				player->setYPosition(obstacle->getBottomBound() - player->getHeight());
				player->setYAccel(player->getYAccel() > 0 ? 0.0f : player->getYAccel());
			}
		}

		obstacle->update();
		obstacle->render();
	}

	shader.unuse();
}

void handleCollisions() {

}

void PlayState::handleInput() {
	if (!player->getIsDead()) {
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
	} else {
		stateManager->loadState(StateManager::MAINMENU);
	}
}