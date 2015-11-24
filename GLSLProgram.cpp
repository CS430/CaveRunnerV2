#include "GLSLProgram.h"
#include <vector>
#include <iostream>
#include <fstream>

GLSLProgram::GLSLProgram() : numAttribute(0), programID(0), vertexShaderID(0), fragShaderID(0) {

}

GLSLProgram::~GLSLProgram() {

}


void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	programID = glCreateProgram();

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (vertexShaderID == 0) {
		std::printf("ERROR : could not create Vertex shader");
	}

	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (fragShaderID == 0) {
		std::printf("ERROR : could not create Fragment shader");
	}

	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragShaderID);
}

void GLSLProgram::linkShaders() {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	//programID = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragShaderID);

	//Link our program
	glLinkProgram(programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(programID);
		//Don't leak shaders either.
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragShaderID);

		//Use the infoLog as you see fit.
		fprintf(stderr, "%s", &errorLog[0]);
		fprintf(stderr, "Shaders failed to link: %s");
		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);
}

/*
void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(programID, numAttribute, attributeName.c_str());
	numAttribute++;
}
*/
void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(programID, numAttribute, attributeName.c_str());
	numAttribute++;
}

GLuint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLuint location =  glGetUniformLocation(programID, uniformName.c_str());
	 
	if (location == GL_INVALID_INDEX) {
		fprintf(stderr, "Error: Uniform: %s ; not found in shader.", uniformName.c_str());
		return NULL;
	} else {
		return location;
	}
}

void GLSLProgram::use() {
	glUseProgram(programID);
	for (int i = 0; i < numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	
	for (int i = 0; i < numAttribute; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string& filepath, GLuint id) {
	std::ifstream vertexFile(filepath);

	if (vertexFile.fail()) {
		fprintf(stderr, "ERROR: Failed to open %s\n", filepath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//We don't need the shader anymore.
		glDeleteShader(id);

		fprintf(stderr, "%s", &errorLog[0]);
		fprintf(stderr, "Shader failed to compile: %s", filepath);

		return;
	}
}