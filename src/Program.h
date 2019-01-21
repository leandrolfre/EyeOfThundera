#pragma once

#include "Bindable.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class UniformAttribute;

using UniformAttributeUPtr = std::unique_ptr<UniformAttribute>;

enum class ShaderType
{
	Vertex,
	Fragment,
	Geometry,
	ShaderTypeMax
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
    UniformAttribute* getUniformByName(const std::string& name);
	void init();
    int uniformAttributesSize();
    UniformAttribute* getUniformAttribute(int i);
    static const char* BUILTIN_HEADER;
    static const char* BUILTIN_UNIFORMS;
    static const char* PROJECTION_MATRIX;
    static const char* MODEL_VIEW_MATRIX;
    static const char* MODEL_VIEW_PROJECTION_MATRIX;
    static const char* NORMAL_MATRIX;
    static const std::vector<std::string> UNIFORM_NAMES;

private:
	void loadBuiltinUniforms();
	std::vector<UniformAttributeUPtr> _uniforms;
	std::unordered_map<std::string, UniformAttribute*> _uniformsByName;
	std::unordered_map<ShaderType, Shader> _shaders;
};