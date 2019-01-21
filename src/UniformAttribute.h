#pragma once

#include <string>
#include <glm/glm.hpp>

class Sampler2D;
class SamplerCube;

union UniformValue 
{
	int intValue;
	float floatValue;
	glm::vec2 vec2;
	glm::vec3 vec3;
	glm::vec4 vec4;
	glm::mat4 mat4;
	Sampler2D* tex2D;
	SamplerCube* texCube;
    UniformValue();
    ~UniformValue();
};

class UniformAttribute 
{
public:
	UniformAttribute();
	~UniformAttribute();
	void setInt(int val);
	void setFloat(float val);
	void setVec2(const glm::vec2& val);
	void setVec3(const glm::vec3& val);
	void setVec4(const glm::vec4& val);
	void setMat4(const glm::mat4& val);
	void setSampler2D(Sampler2D* val);
    void setSamplerCube(SamplerCube* val);
    unsigned int location;
    std::string name;
    UniformValue value;
    unsigned int type;
};
