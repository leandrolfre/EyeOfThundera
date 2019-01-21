#pragma once
#include <glm\glm.hpp>
#include "Shader.h"

class Light
{
public:
	Light();
	virtual ~Light() {}
	
	void setPosition(glm::vec3 position) { _position = position; }
	glm::vec3 getPosition() { return _position; }

	void setDiffuseColor(glm::vec3 diffuse) { _diffuseColor = diffuse; }
	glm::vec3 getDiffuseColor() { return _diffuseColor; }

	void setSpecularColor(glm::vec3 specular) { _specularColor = specular; }
	glm::vec3 getSpecularColor() { return _specularColor; }
	//virtual void pushParams(const Shader& shader, int idx = 0) = 0;
	virtual void draw(const glm::mat4& view, const glm::mat4& proj, const glm::vec3 camPos);

protected:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::vec3 _diffuseColor = glm::vec3(1.0f);
	glm::vec3 _specularColor = glm::vec3(1.0f);
	glm::mat4 _model;
	float _kc;
	float _kl;
	float _kq;
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	unsigned int _textureId;
	//Shader _shader;
};

class DirectionalLight : public Light
{
public:
	glm::vec3 getDirection() { return _position * -1.0f; }
	//void pushParams(const Shader& shader, int idx);
};

class PointLight : public Light
{
public:
	//void pushParams(const Shader& shader, int idx);
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