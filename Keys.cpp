/*
See header file for explination of this class
*/

#include "Keys.h"
#include <GLFW\glfw3.h>

std::vector<bool> Keys::keyState = { false, false, false, false, false, false, false, false, false, false };
std::vector<bool> Keys::previousKeyState = { false, false, false, false, false, false, false, false, false, false };

void Keys::keyPressed(int i, bool b){
	if (i == GLFW_KEY_ENTER){ keyState[Keys::ENTER] = b; }
	else if (i == GLFW_KEY_ESCAPE){ keyState[Keys::ESC] = b; }
	else if (i == GLFW_KEY_SPACE){ keyState[Keys::SPACE] = b; }
	else if (i == GLFW_KEY_W){keyState[Keys::W] = b; }
	else if (i == GLFW_KEY_A){keyState[Keys::A] = b; }
	else if (i == GLFW_KEY_S){keyState[Keys::S] = b; }
	else if (i == GLFW_KEY_D){keyState[Keys::D] = b; }
	else if (i == GLFW_KEY_1){ keyState[Keys::ONE] = b; }
	else if (i == GLFW_KEY_2){ keyState[Keys::TWO] = b; }
	else if (i == GLFW_KEY_3){ keyState[Keys::THREE] = b; }
}

void Keys::update(){
	for (int i = 0; i < Keys::NUMBER_OF_KEYS; i++){
		previousKeyState[i] = keyState[i];
	}
}

bool Keys::isPressed(int x){
	return keyState[x] && !previousKeyState[x];
}

bool Keys::isDown(int x){
	return keyState[x];
}