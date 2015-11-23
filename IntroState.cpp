#include "IntroState.h"

#include <GLFW\glfw3.h>
#include "keys.h"

IntroState::IntroState(StateManager* sm) : stateManager(sm), tick(0), alpha(0.0f), target(400), background(-1.0, -1.0, 2.0, 2.0, backgroundFilePath)
{
	
}

IntroState::~IntroState() 
{

}

void IntroState::init() 
{

	shader.compileShaders("IntroVertShader.glsl", "IntroFragShader.glsl");
	shader.addAttribute("vertexPosition");
	shader.addAttribute("vertexColor");
	shader.addAttribute("vertexUV");
	shader.linkShaders();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void IntroState::update() {
	handleInput();
	
	if (tick < target / 2)
	{
		alpha += 1.0f / (target / 2);
		tick++;
	}
	 else if (tick >= target / 2 && tick < target)
	 {
		alpha -= 1.0f / (target / 2);
		tick++;
	}
	else if (tick >= target)
	{
		 stateManager->loadState(StateManager::MAINMENU);
	}
	else
	{
		fprintf(stderr, "Error: update method - IntorState");
	}
}

void IntroState::render()
{
	shader.use();
	GLint textureLocation = shader.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint alphaValue = shader.getUniformLocation("alphaValue");
	glUniform1f(alphaValue, alpha);

	background.render();

	shader.unuse();

	
}

void IntroState::handleInput() {
	if (Keys::isPressed(Keys::ENTER))
	{
		stateManager->loadState(StateManager::MAINMENU);
	}
}