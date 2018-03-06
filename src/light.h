#pragma once
#include <glm\glm.hpp>

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

protected:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::vec3 _diffuseColor = glm::vec3(1.0f);
	glm::vec3 _specularColor = glm::vec3(1.0f);
	float _kc;
	float _kl;
	float _kq;
};

class DirectionalLight : Light
{
public:
	glm::vec3 getDirection() { return _position * -1.0f; }
};

class PointLight : Light
{

};

class SpotLight : Light
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

/*

struct PointLight {
vec4 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;

};

struct DirLight {
vec3 direction;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};
*/