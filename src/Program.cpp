#include "Program.h"
#include "UniformAttribute.h"
#include <fstream>
#include <sstream>


const char* Program::BUILTIN_HEADER = "#version 330 core \n";

const char* Program::BUILTIN_UNIFORMS =
"uniform mat4 PMatrix;\n"
"uniform mat4 MVMatrix;\n"
"uniform mat4 MVPMatrix;\n"
"uniform mat3 NormalMatrix;\n";

const char* Program::PROJECTION_MATRIX = "PMatrix";
const char* Program::MODEL_VIEW_MATRIX = "MVMatrix";
const char* Program::MODEL_VIEW_PROJECTION_MATRIX = "MVPMatrix";
const char* Program::NORMAL_MATRIX = "NormalMatrix";
const std::vector<std::string> Program::UNIFORM_NAMES = {
    PROJECTION_MATRIX,
    MODEL_VIEW_MATRIX,
    MODEL_VIEW_PROJECTION_MATRIX,
    MODEL_VIEW_PROJECTION_MATRIX
};

Program::Program()
{
}

Program::~Program()
{
}

void Program::init() 
{
    int initialSize = 20;
    _uniforms.reserve(initialSize);
    _uniformsByName.reserve(initialSize);
}

int Program::uniformAttributesSize()
{
    return _uniforms.size();
}

UniformAttribute * Program::getUniformAttribute(int i)
{
    return _uniforms[i].get();
}

void Program::addUniform(UniformAttributeUPtr uniform)
{
    _uniformsByName[uniform->name] = uniform.get();
    _uniforms.push_back(std::move(uniform));
}

void Program::addShader(std::string path, ShaderType type)
{
	std::ifstream shaderFile(path, std::ifstream::in);
	std::stringstream ss;

    ss << BUILTIN_HEADER;
    ss << BUILTIN_UNIFORMS;
	ss << shaderFile.rdbuf();
	_shaders[type] = {path, ss.str(), type};
	shaderFile.close();
}

Shader* Program::getShaderByType(ShaderType type)
{
	return &_shaders[type];
}

UniformAttribute * Program::getUniformByName(const std::string & name)
{
    auto uniform =_uniformsByName.find(name);
    if (uniform != _uniformsByName.end())
    {
        return uniform->second;
    }
    return nullptr;
}

void Program::loadBuiltinUniforms()
{
    for(const auto& uniform : UNIFORM_NAMES)
    {
        auto uniformAttribute = new UniformAttribute();
        uniformAttribute->name = uniform;
        addUniform(UniformAttributeUPtr(uniformAttribute));
    }
}
