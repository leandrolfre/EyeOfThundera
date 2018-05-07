#include "Scene.h"
#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

void Scene::draw()
{
	_shader.use();

	// view/projection transformations
	glm::mat4 projection = _defaultCamera.getProjection();
	glm::mat4 view = _defaultCamera.getView();
	_shader.setMat4("proj", 1, false, glm::value_ptr(projection));
	_shader.setMat4("view", 1, false, glm::value_ptr(view));

	for (int i = 0; i < _lightList.size(); i++) 
	{
		_lightList.at(i)->pushParams(_shader);
	}

	// render the loaded model
	for (int i = 0; i < _modelList.size(); i++)
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 1.8f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		_shader.setMat4("model", 1, false, glm::value_ptr(model));
		_shader.setVec3("cameraPos", _defaultCamera.getX(), _defaultCamera.getY(), _defaultCamera.getZ());
		_modelList.at(i)->draw(_shader);
	}
}

void Scene::addModel(const std::string& modelPath)
{
	_modelList.push_back(std::unique_ptr<Model>(new Model(modelPath)));
}

void Scene::addLight(std::unique_ptr<Light> light)
{
	_lightList.push_back(std::move(light));
}

void Scene::init()
{
	_defaultCamera.setPosition(glm::vec3(0.0, 0.0, 3.0));
	_shader.load("basic.vert", "basic.frag");
}
