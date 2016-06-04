#pragma once
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <vector>

#include "Errors.h"

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

	void linkShaders();

	void addAttribute(const std::string attributeName);

	GLint getUniformLocation(const std::string & uniformName);

	void use();
	void unUse();
private:
	void compileShader(const std::string &shaderPath, GLuint id);

	int _numAttributes;

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

