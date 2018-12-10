#pragma once

#include "Bindable.h"
#include <unordered_map>
#include <memory>

class UniformAttribute;

using UniformAttributeUPtr = std::unique_ptr<UniformAttribute>;

enum class ShaderType
{
	Vertex,
	Fragment,
	Geometry
};

struct Shader {
	std::string path;
	std::string source;
	ShaderType type;
};

class Program : public Bindable 
{
public:
	Program();
	virtual ~Program();
	void addUniform(UniformAttributeUPtr uniform);
	void addShader(std::string path, ShaderType type);
	Shader* getShaderByType(ShaderType type);
private:
	std::unordered_map<std::string, UniformAttribute*> _uniformsByName;
	std::unordered_map<ShaderType, Shader> _shaders;
};