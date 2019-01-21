#include "light.h"
//#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include <iostream>


Light::Light() : _position(0.0f), _diffuseColor(1.0f), _specularColor(1.0f), _kc(0.0f), _kl(0.0f), _kq(0.0f) 
{
	//_shader.load("light.vert", "light.frag");
	//_textureId = TextureManager::getInstance().loadTexture("assets/icons/lamp.png");
	float vertices[] = {
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	/*glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);*/
}

void Light::draw(const glm::mat4& view, const glm::mat4& proj, const glm::vec3 camPos)
{
	//_shader.use();
	//_shader.setInt("texture1", 0);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _textureId);

	//glm::vec3 up(0.0f, 1.0f, 0.0f);
	//glm::vec3 normal = glm::normalize(camPos - _position);
	//glm::vec3 right = glm::cross(normal, up);
	//up = glm::cross(normal, right);

	//glm::mat4 model;
	//model = glm::translate(model, _position); // translate it down so it's at the center of the scene
	//model = model * glm::mat4(	glm::vec4(right, 0.0f), 
	//							glm::vec4(up, 0.0f), 
	//							glm::vec4(normal, 0.0f), 
	//							glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	//						 );

	//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));	// it's a bit too big for our scene, so scale it down
	//auto mvp = proj * view * model;
	//_shader.setMat4("mvp", 1, false, glm::value_ptr(mvp));

	//glBindVertexArray(_vao);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
}

//void PointLight::pushParams(const Shader & shader, int idx)
//{
//	std::string index = std::to_string(idx);
//	shader.setVec3("pointLight[" + index + "].position", _position);
//	shader.setVec3("pointLight[" + index + "].diffuse", _diffuseColor);
//	shader.setVec3("pointLight[" + index + "].specular", _specularColor);
//	shader.setVec3("pointLight[" + index + "].ambient", glm::vec3(0.6f, 0.6f, 0.6f));
//	shader.setFloat("pointLight[" + index + "].kc", 1.0f);
//	shader.setFloat("pointLight[" + index + "].kl", 0.007f);
//	shader.setFloat("pointLight[" + index + "].kq", 0.0002f);
//}
//
//void DirectionalLight::pushParams(const Shader & shader, int idx)
//{
//
//	shader.setVec3("dirLight.position", _position);
//	shader.setVec3("dirLight.diffuse", _diffuseColor);
//	shader.setVec3("dirLight.specular", _specularColor);
//	shader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//	shader.setVec3("dirLight.direction", this->getDirection());
//}
