#include "Program.h"
#include "Bindable.h"
#include <fstream>
#include <sstream>

Program::Program()
{
}

Program::~Program()
{
}

void Program::addUniform(UniformAttributeUPtr uniform)
{
}

void Program::addShader(std::string path, ShaderType type)
{
	std::ifstream shaderFile(path, std::ifstream::in);
	std::stringstream ss;

	ss << shaderFile.rdbuf();
	shaderFile.close();
	_shaders[type] = {path, ss.str(), type};
	shaderFile.close();
}

Shader* Program::getShaderByType(ShaderType type)
{
	return &_shaders[type];
}