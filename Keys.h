/*
	This is our class that will handle user input.
	we will define the keys we are listening for in this class. 
	we will set the key state in the GameScreen and check specific keys 
	states in the state class. we do this because each state is going 
	to handle input differently i.e. in the Main menu w and s may navigate through 
	menu options, but in the play state w and s will controll the player.


	ex in play state
	handleInput()
	{
		if Keys.ispressed("s")
		{
			player.setXPos(player.getXpos() + 5);
		}
	}

	or something similiar to this.

*/

#pragma once

#ifndef KEYS_H
#define KEYS_H

#include <vector>

class Keys
{

	static std::vector<bool> keyState;
	static std::vector<bool> previousKeyState;
public:


	static void keyPressed(int i, bool b);
	static void update();
	static bool isPressed(int x);
	static bool isDown(int x);

	static const int NUMBER_OF_KEYS = 7;

	static const int ENTER = 0;
	static const int ESC = 1;
	static const int SPACE = 2;
	static const int W = 3;
	static const int A = 4;
	static const int S = 5;
	static const int D = 6;



};




#endif