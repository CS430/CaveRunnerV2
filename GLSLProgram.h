#pragma once

#include <string>
#include <GL/glew.h>


#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H
class GLSLProgram
{

public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);


	void use();
	void unuse();

private:

	int numAttribute;

	void compileShader(const std::string& filepath, GLuint id);
	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragShaderID;

};


#endif