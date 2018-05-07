#pragma once
#include <vector>
#include <string>
#include <memory>
#include "shader.hpp"
#include "model.h"
#include "camera.hpp"
#include "light.h"

class Scene 
{
public:
	Scene() = default;
	void init();
	void draw();
	void addModel(const std::string& modelPath);
	void addLight(std::unique_ptr<Light> light);
	Camera& getCurrentCamera() { return _defaultCamera; }
private:
	std::vector<std::unique_ptr<Model>> _modelList;
	std::vector<std::unique_ptr<Light>> _lightList;
	Camera _defaultCamera;
	Shader _shader;

};