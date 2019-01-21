#pragma once

#include "Shader.h"

class Camera;

class Skybox
{
public:
	Skybox() = default;
	void draw(const Camera& camera);
	void init();
	inline unsigned int getTexture() const { return _textureId; }
private:
	unsigned int _textureId = { 0 };
	unsigned int _vao = { 0 };
	unsigned int _vbo = { 0 };
	//Shader _shader;

};