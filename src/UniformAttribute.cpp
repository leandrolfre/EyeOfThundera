#include "UniformAttribute.h"
#include "Texture.h"

UniformAttribute::UniformAttribute()
{
}

UniformAttribute::~UniformAttribute()
{
}

void UniformAttribute::setInt(int val)
{
	_value.intValue = val;
}

void UniformAttribute::setFloat(float val)
{
	_value.floatValue = val;
}

void UniformAttribute::setVec2(const glm::vec2 & val)
{
	_value.vec2 = val;
}

void UniformAttribute::setVec3(const glm::vec3 & val)
{
	_value.vec3 = val;
}

void UniformAttribute::setVec4(const glm::vec4 & val)
{
	_value.vec4 = val;
}

void UniformAttribute::setMat4(const glm::mat4 & val)
{
	_value.mat4 = val;
}

void UniformAttribute::setTexture(Texture* val)
{
	_value.texture = val;
}

UniformValue::UniformValue()
{
}

UniformValue::~UniformValue()
{
}
