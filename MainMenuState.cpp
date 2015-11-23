
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "MainMenuState.h"
#include "ImageLoader.h"
#include "Keys.h"


MainMenuState::MainMenuState(StateManager* sm) : stateManager(sm), labels(2), index(0) //, playLb(-.2f, -.2f, playTextureFilePath), quitLb(-.2f, -.4f, quitTextureFilePath){
{
	labels[0] = new Label(-0.2f, -0.2f, 0.3, 0.1, playTextureFilePath);
	labels[1] = new Label(-0.2f, -0.4f, 0.3, 0.1, quitTextureFilePath);

}

MainMenuState::~MainMenuState() {

}

void MainMenuState::init()
{

	shader.compileShaders("MenuVertShader.glsl", "MenuFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();

	labels[0]->setSelected(1);

	glClearColor(0.0, 0.0, 0.0, 1.0f);
	
}

void MainMenuState::update() {
	
	handleInput();
	


}

void MainMenuState::render() 
{
	shader.use();

	GLint textureLocation = shader.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);


	GLint selectedLocation = shader.getUniformLocation("selected");
	glUniform1i(selectedLocation, labels[0]->isSelected());

	//sprite.render();
	labels[0]->render();
	glUniform1i(selectedLocation, labels[1]->isSelected());
	labels[1]->render();

	shader.unuse();
}

void MainMenuState::handleInput()
{
	if (Keys::isPressed(Keys::W))
	{
		if (index > 0)
		{
			index--;
			labels[0]->setSelected(1);
			labels[1]->setSelected(0);
		}
		fprintf(stderr, "w pressed in mmState!  %d \n", index);

	}
	else if (Keys::isPressed(Keys::S))
	{
		if (index < maxIndex)
		{
			index++;
			labels[1]->setSelected(1);
			labels[0]->setSelected(0);
		}
		fprintf(stderr, "s pressed in mmState! %d \n", index);

	}
	else if (Keys::isPressed(Keys::ENTER))
	{
		if (index == 0)
		{
			stateManager->loadState(StateManager::PLAY);
		}
		if (index == 1)
		{
			//quit game
		}
	}
}