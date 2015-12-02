#include "IntroState.h"

#include <GLFW\glfw3.h>
#include "keys.h"

GLint textureLocation;
GLint alphaValue;

IntroState::IntroState(StateManager* sm) : stateManager(sm), tick(0), alpha(0.0f), target(200), background(0.0, 0.0, 1.0, 1.0, backgroundTex) {

}

IntroState::~IntroState() {

}

void IntroState::init() {
	shader.compileShaders("IntroVertShader.glsl", "IntroFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();

	textureLocation = shader.getUniformLocation("mySampler");
	alphaValue = shader.getUniformLocation("alphaValue");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void IntroState::update() {
	handleInput();

	if (tick < target / 3) {
		alpha += 1.0f / (target / 3);
		tick++;
	}
	else if (tick >= target / 3 && tick < 2 * target / 3) {
		tick++;
	}
	else if (tick >= target / 3 && tick < target) {
		alpha -= 1.0f / (target / 3);
		tick++;
	}
	else if (tick >= target) {
		stateManager->loadState(StateManager::MAINMENU);
	}
}

void IntroState::render() {
	shader.use();
	glUniform1i(textureLocation, 0);
	glUniform1f(alphaValue, alpha);

	background.render();

	shader.unuse();
}

void IntroState::handleInput() {
	if (Keys::isPressed(Keys::ENTER)) {
		stateManager->loadState(StateManager::MAINMENU);
	}
}