#include "light.h"
#include "shader.hpp"

void PointLight::pushParams(const Shader & shader)
{

	shader.setVec3("pointLight[0].position", _position);
	shader.setVec3("pointLight[0].diffuse", _diffuseColor);
	shader.setVec3("pointLight[0].specular", _specularColor);
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setFloat("pointLight[0].kc", 1.0f);
	shader.setFloat("pointLight[0].kl", 0.09f);
	shader.setFloat("pointLight[0].kq", 0.032f);
}
