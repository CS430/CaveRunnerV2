#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "MainMenuState.h"
#include "ImageLoader.h"
#include "Keys.h"

GLint menuTextureLocation;
GLint selectedLocation;

MainMenuState::MainMenuState(StateManager* sm) : stateManager(sm), labels(2), index(0) { //, playLb(-.2f, -.2f, playTextureFilePath), quitLb(-.2f, -.4f, quitTextureFilePath){ 
	labels[0] = new Label(0.0f, 0.25f, 0.25, 0.15, playTex);
	labels[1] = new Label(0.0f, -0.25f, 0.25, 0.15, quitTex);
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::init() {
	shader.compileShaders("MenuVertShader.glsl", "MenuFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();

	menuTextureLocation = shader.getUniformLocation("mySampler");
	selectedLocation = shader.getUniformLocation("selected");

	labels[0]->setSelected(1);

	glClearColor(0.0, 0.0, 0.0, 1.0f);
}

void MainMenuState::update() {
	handleInput();
}

void MainMenuState::render() {
	shader.use();

	glUniform1i(menuTextureLocation, 0);
	glUniform1i(selectedLocation, labels[0]->isSelected());

	//sprite.render();
	labels[0]->render();
	glUniform1i(selectedLocation, labels[1]->isSelected());
	labels[1]->render();

	shader.unuse();
}

void MainMenuState::handleInput() {
	if (Keys::isPressed(Keys::W)) {
		if (index > 0) {
			index--;
			labels[0]->setSelected(1);
			labels[1]->setSelected(0);
		}
	}
	else if (Keys::isPressed(Keys::S)) {
		if (index < maxIndex) {
			index++;

			labels[1]->setSelected(1);
			labels[0]->setSelected(0);
		}
	}
	else if (Keys::isPressed(Keys::ENTER)) {
		if (index == 0) {
			stateManager->loadState(StateManager::PLAY);
		}

		if (index == 1) {
			glfwTerminate();
		}
	}
	else if (Keys::isPressed(Keys::ESC)) {
		glfwTerminate();
	}
}