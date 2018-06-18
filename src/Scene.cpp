#include "Scene.h"
#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "light.h"
#include "model.h"

void Scene::draw()
{	
	// view/projection transformations
	glm::mat4 projection = _defaultCamera.getProjection();
	glm::mat4 view = _defaultCamera.getView();

	/*_shader.use();
	_shader.setMat4("proj", 1, false, glm::value_ptr(projection));
	_shader.setMat4("view", 1, false, glm::value_ptr(view));
	_shader.setVec3("cameraPos", _defaultCamera.getPosition());*/

	for (int i = 0; i < _lightList.size(); i++) 
	{
		_lightList.at(i)->pushParams(_shader, i);
	}
	_reflection.use();
	_reflection.setVec3("cameraPos", _defaultCamera.getPosition());
	_reflection.setFloat("fresnelBias", _fresnelBias);
	_reflection.setFloat("fresnelScale", _fresnelScale);
	_reflection.setFloat("fresnelPower", _fresnelPower);
	//render the loaded model
	for (int i = 0; i < _modelList.size(); i++)
	{
		auto mvp = projection * view * _modelList.at(i)->getModel();
		_reflection.setMat4("model", 1, false, glm::value_ptr(_modelList.at(i)->getModel()));
		_reflection.setMat4("mvp", 1, false, glm::value_ptr(mvp));
		glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox.getTexture());
		_modelList.at(i)->draw(_reflection);
	}

	for (int i = 0; i < _lightList.size(); i++)
	{
		_lightList.at(i)->draw(view, projection, _defaultCamera.getPosition());
	}

	_skybox.draw(_defaultCamera);
}

void Scene::update(float dt) 
{
	for (int i = 0; i < _modelList.size(); i++)
	{
		_modelList.at(i)->rotate(glm::vec3(0.0, 1.0f, 0.0), dt);
	}
}
void Scene::addModel(std::unique_ptr<Model> model)
{
	_modelList.push_back(std::move(model));
}

void Scene::addLight(std::unique_ptr<Light> light)
{
	_lightList.push_back(std::move(light));
}

void Scene::init()
{
	_defaultCamera.setPosition(glm::vec3(0.0, 0.0, 20.0));
	//_shader.load("basic.vert", "basic.frag");
	_reflection.load("reflection.vert", "reflection.frag");
	_skybox.init();
}

void Scene::incBias() 
{ 
	_fresnelBias += 0.01f; 
}

void Scene::decBias() 
{ 
	_fresnelBias -= 0.01f;
}

void Scene::incScale() 
{ 
	_fresnelScale += 0.01f;
}

void Scene::decScale() 
{ 
	_fresnelScale -= 0.01f;
}

void Scene::incPower() 
{ 
	_fresnelPower += 0.01f;
}

void Scene::decPower() 
{ 
	_fresnelPower -= 0.01f;
}