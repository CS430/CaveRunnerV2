#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <GLFW\glfw3.h>
#include "StateManager.h"
#include "GLSLProgram.h"
#include "Sprite.h"

class GameScreen {
public:
	GameScreen();		//constructor
	~GameScreen();		//destructor

	void run();			//will hold the main game loop
	
	void initSystems();	//called by run, sets up our window and stuff like that

	/*
		will update all of the game logic. this will call the statemanagers update which will call the current 
		states update fucntion which will call all of the entities withing that states update method.
	*/
	void update();		

	/*
		Similiar to update but will call the render methods.
		we may need to pass some type of data strucure( vector or array) or two in the render method that each object can write its verticies to , along with their color data.
	*/
	void render();

	/*
		we may not need this but i think this will only have the glfwswapbuffers function. 
		it may also have the gl_draw_triangles in it, it depends on what actually shows stuff on the screen. i think how it works is that we draw
		to the back buffer and then when we want to show it we swap buffers so that things arnt being draw directly to the screen because that causes 
		tearing and flickering. if this is the case we should be calling glDrawTri in every render call then just call swap buffer in the dray.
	*/
	void draw();

	/*
	because we are going to create a class that helps manage user input we are going to wrapp glfwpoll events in this handleInput function
	wich will act as our link between our input class and the glfwPollevents
	we will set keys in GameScreen, but check keys in our states.
	*/
	static void handleInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void end();

private:
	//we do not want to resize the window
	const int WIDTH = 960;
	const int HEIGHT = 540;
	const char* TITLE = "CaveRunner";

	const int TARGET_FPS = 60;
	const double TARGET_TIME = 1000 / TARGET_FPS;
	float averageFPS;

	int frameCount;
	double startTime;
	double exeTime;
	double sleepTime;
	double totalTime;

	GLFWwindow* window;
	StateManager stateManager;
	//GLSLProgram shader;
	//Sprite sprite;
};

#endif