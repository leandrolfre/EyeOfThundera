#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad\glad.h>

void Shader::load(const char* vertexPath, const char* fragmentPath) 
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* vertCode, *fragCode;
	
	std::ifstream vertexFile(vertexPath), fragmentFile(fragmentPath);
	std::stringstream vStream, fStream;

	vStream << vertexFile.rdbuf();
	fStream << fragmentFile.rdbuf();

	std::string vstr = vStream.str();
	std::string fstr = fStream.str();

	vertCode = vstr.c_str();
	fragCode = fstr.c_str();

	vertexFile.close();
	fragmentFile.close();

	glShaderSource(vertexShader, 1, &vertCode, nullptr);
	glCompileShader(vertexShader);

	glShaderSource(fragShader, 1, &fragCode, nullptr);
	glCompileShader(fragShader);
	
	checkError(vertexShader);
	checkError(fragShader);

	_id = glCreateProgram();
	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragShader);
	glLinkProgram(_id);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::checkError(unsigned int shader) const 
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::use() 
{
	glUseProgram(_id);
}

void Shader::setBool(const std::string &name, bool value) const 
{
	glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const 
{
	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const 
{
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, unsigned int count, bool transpose, const float* value) const
{
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), count, transpose, value);
}

void Shader::setVec3(const std::string & name, const float x, const float y, const float z) const
{
	glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string & name, const float x, const float y, const float z, const float w) const
{
	glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
}
