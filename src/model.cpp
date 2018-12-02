//#include "model.h"
//#include "Shader.h"
//#include "mesh.h"
//
//#include <iostream>
//#include "TextureManager.h"
//#include <memory>
//#include <glm\gtc\type_ptr.hpp>
//
//Model::Model(const std::string& path) : _scale(1.0f)
//{
//	loadModel(path);
//}
//
//void Model::draw(const Shader& shader)
//{
//	for (int i = 0; i < _meshes.size(); i++) 
//	{
//		_meshes[i].draw(shader);
//	}
//}
//
//void Model::loadModel(const std::string& path)
//{
//	
//}
//
//void Model::setPosition(glm::vec3 pos) 
//{ 
//	_position = pos;
//	_model = glm::scale(glm::mat4(1.0f), _scale);
//	_model = glm::translate(_model, pos); 
//}
//
//void Model::setScale(float scale) 
//{ 
//	_scale = glm::vec3(scale);
//	_model = glm::scale(glm::mat4(1.0f), _scale);
//	_model = glm::translate(_model, _position);
//}
//
//void Model::rotate(glm::vec3 axis, float angle)
//{
//	_model = glm::rotate(_model, angle, axis);
//}
