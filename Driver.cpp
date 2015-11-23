#include <iostream>

#include "GLSLProgram.h"
#include "GameScreen.h"

int main(void) {
	GameScreen game;

	game.run();

	return 0;
}

/*
GLSLProgram shaders;
shaders.compileShaders("VertexShader.glsl", "FragmentShader.glsl");
shaders.linkShaders();
//	GLuint programID = LoadShaders("vertexshader.glsl", "fragmentshader.glsl");

GLfloat g_vertex_buffer_data[] = {
0, 0, 0,
1, 0, 0,
.5, 1, 0
};

GLfloat g_color_buffer_data[] = {
1, 0, 0,
0, 1, 0,
0, 0, 1
};

GLuint vertexbuffer;
glGenBuffers(0, &vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

GLuint colorbuffer;
glGenBuffers(1, &colorbuffer);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

//Main Loop
do {
glClear(GL_COLOR_BUFFER_BIT);
//glUseProgram(programID);

glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
0,
3,
GL_FLOAT,
GL_FALSE,
0,
(void*)0
);

glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glVertexAttribPointer(
1,
3,
GL_FLOAT,
GL_FALSE,
0,
(void*)0
);

shaders.use();

glDrawArrays(GL_TRIANGLES, 0, 3);

shaders.unuse();

glDisableVertexAttribArray(0);
glDisableVertexAttribArray(1);

glfwSwapBuffers(window);
glfwPollEvents();

} while (!glfwWindowShouldClose(window));

glDeleteBuffers(1, &vertexbuffer);
glDeleteBuffers(1, &colorbuffer);
//glDeleteProgram(programID);
glDeleteVertexArrays(1, &VertexArrayID);

glfwDestroyWindow(window);

glfwTerminate();

*/