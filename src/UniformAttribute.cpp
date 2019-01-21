#include "UniformAttribute.h"
#include "Sampler.h"

UniformAttribute::UniformAttribute()
{
}

UniformAttribute::~UniformAttribute()
{
}

void UniformAttribute::setInt(int val)
{
	value.intValue = val;
}

void UniformAttribute::setFloat(float val)
{
    value.floatValue = val;
}

void UniformAttribute::setVec2(const glm::vec2 & val)
{
    value.vec2 = val;
}

void UniformAttribute::setVec3(const glm::vec3 & val)
{
    value.vec3 = val;
}

void UniformAttribute::setVec4(const glm::vec4 & val)
{
    value.vec4 = val;
}

void UniformAttribute::setMat4(const glm::mat4 & val)
{
    value.mat4 = val;
}

void UniformAttribute::setSampler2D(Sampler2D * val)
{
    value.tex2D = val;
}

void UniformAttribute::setSamplerCube(SamplerCube * val)
{
    value.texCube = val;
}

UniformValue::UniformValue()
{
}

UniformValue::~UniformValue()
{
}
