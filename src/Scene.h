//#pragma once
//#include <vector>
//#include <string>
//#include <memory>
//#include "Shader.h"
//#include "camera.hpp"
//#include "Skybox.h"
//
//class Light;
////class Model;
//
//class Scene 
//{
//public:
//	Scene() = default;
//	void init();
//	void draw();
//	void update(float dt);
//	//void addModel(std::unique_ptr<Model> model);
//	void addLight(std::unique_ptr<Light> light);
//	Camera& getCurrentCamera() { return _defaultCamera; }
//	void incBias();
//	void decBias();
//	void incScale();
//	void decScale();
//	void incPower();
//	void decPower();
//private:
//	//std::vector<std::unique_ptr<Model>> _modelList;
//	std::vector<std::unique_ptr<Light>> _lightList;
//	Camera _defaultCamera;
//	Shader _shader;
//	Shader _reflection;
//	Skybox _skybox;
//	float _fresnelBias = {0.0f};
//	float _fresnelScale = { 0.0f };
//	float _fresnelPower = { 0.0f };
//};