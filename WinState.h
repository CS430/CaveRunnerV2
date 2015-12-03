#ifndef WIN_STATE_H
#define WIN_STATE_H

#include "State.h"
#include "GLSLProgram.h"
#include "Background.h"
#include "ImageLoader.h"

class WinState : public State {
public:
	WinState(StateManager *sm);
	~WinState();

	void init();
	void update();
	void render();
	void handleInput();

private:
	int tick;
	float alpha;
	int target;

	const GLTexture backgroundTex = ImageLoader::loadPNG("Resources/Images/win_splash.png");

	StateManager* stateManager;

	GLSLProgram shader;

	Background background;
};

#endif