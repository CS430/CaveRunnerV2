#include "Label.h"

Label::Label(float startX, float startY, float startW, float startH, GLTexture texture) : Entity(startX, startY, startW, startH, texture), selected(0) {
	objSprite.init();
}

Label::~Label() {

}

void Label::update() {
	//TO-DO:: may need to do something here but for labels i dont think we need much.
}

void Label::render() {
	//glEnable(GL_BLEND);							//moved to GameScreen initSystems function because we always want alpha values to matter
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objTexture.id);

	objSprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

int Label::isSelected() {
	return selected;
}

void Label::setSelected(int state) {
	selected = state;
}