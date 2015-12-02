#include "PlayState.h"
#include "Keys.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

std::vector<Obstacle*> lvl1Obstacles;
std::vector<Obstacle*> lvl2Obstacles;
std::vector<Obstacle*> lvl3Obstacles;

Exit *lvl1Exit;
Exit *lvl2Exit;
Exit *lvl3Exit;

int currentStage;

GLint playTextureLocation;
GLint matrixId;

glm::mat4 Projection;
glm::mat4 Model;

PlayState::PlayState(StateManager *sm) : stateManager(sm), background(0.0f, 0.0f, 2.0f, 1.1f, backgroundFilePath) {
	glClearColor(0.153f, 0.051f, 0.0f, 0.0f);

	lvl1Obstacles = {
		new Obstacle(-0.6f, -1.0f, 1.5f, 0.1f, obstacleTexFilePath),
		new Obstacle(0.4f, -0.8f, 0.1f, 0.1f, obstacleTexFilePath),
		new Obstacle(0.6f, -0.7f, 0.1f, 0.2f, obstacleTexFilePath),
		new Obstacle(0.8f, -0.5f, 0.1f, 0.4f, obstacleTexFilePath),
		new Obstacle(2.55f, -1.0f, 0.8f, 0.1f, obstacleTexFilePath),
	};

	lvl2Obstacles = {
		new Obstacle(0.0f, -1.0f, 3.0f, 0.1f, obstacleTexFilePath)
	};

	lvl3Obstacles = {
		new Obstacle(-0.65f, -0.7f, 0.2f, 0.2f, obstacleTexFilePath),
		new Obstacle(-0.95f, -0.5f, 0.275f, 0.5f, obstacleTexFilePath),
		new Obstacle(0.9f, 0.4f, 0.25f, 0.1f, obstacleTexFilePath),
		new Obstacle(0.7f, 0.9f, 0.05f, 0.25f, obstacleTexFilePath),
		new Obstacle(-0.60f, -1.0f, 0.65f, 0.1f, obstacleTexFilePath),
		new Obstacle(-1.85f, -0.0f, 0.75f, 1.1f, obstacleTexFilePath),
		new Obstacle(4.0f, -1.0f, 0.025f, 0.5f, obstacleTexFilePath),
		new Obstacle(4.25f, -1.0f, 0.025f, 0.95f, obstacleTexFilePath),
		new Obstacle(4.5f, -1.0f, 0.025f, 1.4f, obstacleTexFilePath)
	};

	obstacles = lvl1Obstacles;

	player = new Player(0.0f, 0.0f, 0.04f, 0.08f, playerTexFilePath);

	lvl1Exit = new Exit(3.0f, -0.825f, 0.0375f, 0.075f, exitTexFilePath);
	lvl2Exit = new Exit(0.5f, -0.825f, 0.0375f, 0.075f, exitTexFilePath);
	lvl3Exit = new Exit(4.5f, 0.475f, 0.0375f, 0.075f, exitTexFilePath);

	exit = lvl1Exit;

	currentStage = 1;
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

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(3.0f, 1.0f, 0.1f, 1.0f);

	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f) * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0.25f);
}

void PlayState::update() {
	handleInput();
}

void PlayState::render() {
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(player->getXPosition() * 4.0f, 0, 0.3f), // Camera is at (4,3,-3), in World Space
		glm::vec3(player->getXPosition() * 4.0f, 0.0f, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	shader.use();

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(playTextureLocation, 0);

	background.setXPosition(player->getXPosition() / 1.05f);
	background.update();
	background.render();

	exit->render();

	player->update();
	player->render();

	for (Obstacle *obstacle : obstacles) {
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

		obstacle->render();
	}

	if (player->getBottomBound() < exit->getTopBound()
		&& player->getTopBound() > exit->getBottomBound()
		&& player->getLeftBound() < exit->getXPosition()
		&& player->getRightBound() > exit->getXPosition()) {

		if (currentStage == 1) {
			obstacles = lvl2Obstacles;
			exit = lvl2Exit;
		} else if (currentStage == 2) {
			obstacles = lvl3Obstacles;
			exit = lvl3Exit;
		}

		player->setXPosition(0.0f);
		player->setYPosition(0.0f);
		player->setXAccel(0.0f);
		player->setYAccel(0.0f);

		currentStage++;
	}

	shader.unuse();
}

void PlayState::handleInput() {
	if (Keys::isDown(Keys::ONE)) {
		obstacles = lvl1Obstacles;
		exit = lvl1Exit;
		currentStage = 1;

		player = new Player(0.0f, 0.0f, 0.04f, 0.08f, playerTexFilePath);
	} else if (Keys::isDown(Keys::TWO)) {
		obstacles = lvl2Obstacles;
		exit = lvl2Exit;
		currentStage = 2;

		player = new Player(0.0f, 0.0f, 0.04f, 0.08f, playerTexFilePath);
	} else if (Keys::isDown(Keys::THREE)) {
		obstacles = lvl3Obstacles;
		exit = lvl3Exit;
		currentStage = 3;

		player = new Player(0.0f, 0.0f, 0.04f, 0.08f, playerTexFilePath);
	} else if (Keys::isPressed(Keys::ESC)) {
		stateManager->loadState(StateManager::PAUSED);
	}

	if (!player->getIsDead()) {
		if (Keys::isDown(Keys::S)) {
			player->setIsCrouching(true);
		} else {
			player->setTexture(player->getIsFacingRight() ? player->idleRight : player->idleLeft);
			player->setIsCrouching(false);
		}

		if (Keys::isDown(Keys::D)) {
			if (!player->getIsCrouching() && player->getXAccel() < player->maxPlayerSpeed) {
				float accel = !player->getHasJumped() ? player->playerAcccel : (player->playerAcccel * player->airResistance);
					
				player->setXAccel(player->getXAccel() + accel);
			}

			player->setTexture(player->runRight);
			player->setIsFacingRight(true);
		}

		if (Keys::isDown(Keys::A)) {
			if (!player->getIsCrouching() && player->getXAccel() > -player->maxPlayerSpeed) {
				float accel = !player->getHasJumped() ? player->playerAcccel : (player->playerAcccel * player->airResistance);

				player->setXAccel(player->getXAccel() - accel);
			}

			player->setTexture(player->runLeft);
			player->setIsFacingRight(false);
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
	} else {
		stateManager->loadState(StateManager::MAINMENU);
	}
}