#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Windows.h>

#include "GameScreen.h"
#include "StateManager.h"
#include "Keys.h"
#include "GLSLProgram.h"


GameScreen::GameScreen(){

}

GameScreen::~GameScreen() {

}

void GameScreen::run() {
	initSystems();

	while (!glfwWindowShouldClose(window)) 
	{
		
		startTime = glfwGetTime();

		update();
		render();

		exeTime = glfwGetTime() - startTime;
		sleepTime = TARGET_TIME - exeTime;

		if (sleepTime > 0)
		{
			Sleep(sleepTime);
		}

		totalTime += glfwGetTime() - startTime;
		frameCount++;
		if (frameCount == TARGET_FPS)
		{
			averageFPS = frameCount / totalTime;
			fprintf(stderr, "average FPS: %lf \n", averageFPS);

			frameCount = 0;
			totalTime = 0;
		}

		glfwPollEvents();
	}

	end();
}



void GameScreen::initSystems() {
	/*----------------------------------------------------*/
	//INIT GLFW
	/*----------------------------------------------------*/

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not initilize GLFW. \n");
		exit(EXIT_FAILURE);
	}

	GameScreen::window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	if (!window) {
		fprintf(stderr, "ERROR: Failed to open GLFW Window. \n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	/*----------------------------------------------------*/
	//INIT GLEW
	/*----------------------------------------------------*/
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	/*----------------------------------------------------*/
	//INIT VAO
	/*----------------------------------------------------*/
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*----------------------------------------------------*/
	//INIT Our Systems
	/*----------------------------------------------------*/
	glfwSetKeyCallback(window, handleInput);
	stateManager.init();


	//shader.compileShaders("VertexShader.glsl", "FragmentShader.glsl");
	//shader.addAttribute("vertexPosition");
	//shader.linkShaders();
	//sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
}



void GameScreen::update() {
	stateManager.update();
	Keys::update();
}



void GameScreen::render() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	stateManager.render();

//	shader.use();
//	sprite.draw();
//	shader.unuse();

	glfwSwapBuffers(window);
}



void GameScreen::draw() 
{

}



void GameScreen::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Keys::keyPressed(key, true);
	}
	else if (action == GLFW_RELEASE)
	{
		Keys::keyPressed(key, false);
	}

}



void GameScreen::end()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}