#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!_vertexShaderID)
	{
		fatalError("Vertex shader failed to be created!");
	}

	compileShader(vertexShaderPath, _vertexShaderID);

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!_fragmentShaderID)
	{
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(fragmentShaderPath, _fragmentShaderID);
}

void GLSLProgram::linkShaders()
{
	
	if (!_programID)
	{
		fatalError("Could not create shader program!");
	}

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	
	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (!isLinked)
	{
		/*
		##############################
		NEED TO ADD ERROR LOG FOR THIS
		##############################
		*/
		fatalError("Shader program could not be linked!");
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unUse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string & shaderPath, GLuint id)
{
	std::ifstream shaderFile(shaderPath);
	if (shaderFile.fail())
	{
		perror(shaderPath.c_str());
		fatalError("Failed to open " + shaderPath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line))
	{
		fileContents += line + '\n';
	}

	shaderFile.close();

	const char* shaderContentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &shaderContentsPtr, nullptr);

	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + shaderPath + " failed to compile");
	}
}

void GLSLProgram::addAttribute(const std::string attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string &uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " could not be found in shader!");
	}
	return location;
}