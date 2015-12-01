#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>

Vertex vertexData[6]; //2 values for each vertex, 6 different verticies.

Sprite::Sprite(float initX, float initY, float initWidth, float initHeight) : x(initX), y(initY), width(initWidth), height(initHeight), vboID(0), vertexPosition(6) {

}

void Sprite::init() {
	if (vboID == 0)	{
		glGenBuffers(1, &vboID);
	}

	update();
}

Sprite::~Sprite() {
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);	//setting vboID to a value thats not 0
	}
}


void Sprite::update() {
	//first triangle
	//top right
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	//top left
	vertexData[1].setPosition(x - width, y + height);
	vertexData[1].setUV(0.0f, 1.0f);

	//bottom left
	vertexData[2].setPosition(x - width, y - height);
	vertexData[2].setUV(0.0f, 0.0f);

	//second triangle
	//bottom left
	vertexData[3].setPosition(x - width, y - height);
	vertexData[3].setUV(0.0f, 0.0f);

	//bottom right
	vertexData[4].setPosition(x + width, y - height);
	vertexData[4].setUV(1.0f, 0.0f);

	//top right
	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite:: render() {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0);

	//position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//uv attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::setX(float newX) {
	x = newX;
}

void Sprite::setY(float newY) {
	y = newY;
}

void Sprite::setH(float newH) {
	height = newH;
}

void Sprite::setW(float newW) {
	width = newW;
}