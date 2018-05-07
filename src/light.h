#pragma once
#include <glm\glm.hpp>

class Shader;

class Light
{
public:
	Light() : _position(0.0f), _diffuseColor(1.0f), _specularColor(1.0f), _kc(0.0f), _kl(0.0f), _kq(0.0f)  {}
	virtual ~Light() {}
	
	void setPosition(glm::vec3 position) { _position = position; }
	glm::vec3 getPosition() { return _position; }

	void setDiffuseColor(glm::vec3 diffuse) { _diffuseColor = diffuse; }
	glm::vec3 getDiffuseColor() { return _diffuseColor; }

	void setSpecularColor(glm::vec3 specular) { _specularColor = specular; }
	glm::vec3 getSpecularColor() { return _specularColor; }
	virtual void pushParams(const Shader& shader) = 0;

protected:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::vec3 _diffuseColor = glm::vec3(1.0f);
	glm::vec3 _specularColor = glm::vec3(1.0f);
	float _kc;
	float _kl;
	float _kq;
};

class DirectionalLight : public Light
{
public:
	glm::vec3 getDirection() { return _position * -1.0f; }
};

class PointLight : public Light
{
	void pushParams(const Shader& shader);
};

class SpotLight : public Light
{
public:
	void setInnerCutOff(float inner) { _innerCutOff = inner; }
	float getInnerCutOff() { return  _innerCutOff; }

	void setOuterCutOff(float outer) { _outerCutOff = outer; }
	float getOuterCutOff() { return  _outerCutOff; }
private:
	float _innerCutOff;
	float _outerCutOff;
};