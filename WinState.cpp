#include "WinState.h"

#include <GLFW\glfw3.h>
#include "keys.h"

GLint textureLocation;
GLint winAlpha;

WinState::WinState(StateManager* sm) : stateManager(sm), tick(0), alpha(0.0f), target(300), background(0.0, 0.0, 1.0, 1.0, backgroundTex) {

}

WinState::~WinState() {

}

void WinState::init() {
	shader.compileShaders("WinVertShader.glsl", "WinFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();

	textureLocation = shader.getUniformLocation("mySampler");
	winAlpha = shader.getUniformLocation("winAlpha");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void WinState::update() {
	handleInput();

	if (tick < target) {
		alpha += 1.0f / target;
		tick++;
	}
	else if (tick >= target) {
		stateManager->loadState(StateManager::MAINMENU);
	}
}

void WinState::render() {
	shader.use();
	glUniform1i(textureLocation, 0);
	glUniform1f(winAlpha, alpha);

	background.render();

	shader.unuse();
}

void WinState::handleInput() {
	if (Keys::isPressed(Keys::ENTER)) {
		stateManager->loadState(StateManager::MAINMENU);
	}
}