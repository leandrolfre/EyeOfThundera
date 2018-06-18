#pragma once

#include <string>
#include <vector>
#include <assimp\scene.h>
#include <unordered_map>
#include "Material.h"
#include "mesh.h"
#include <glm/gtc/matrix_transform.hpp>

class Shader;

class Model 
{
public:
	Model(const std::string& path);
	void draw(const Shader& shader);
	void setPosition(glm::vec3 pos);
	void setScale(float scale);
	void rotate(glm::vec3 axis, float angle);
	glm::mat4 getModel() { return _model; }

private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	Texture Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName);

private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	glm::mat4 _model;
	glm::vec3 _scale;
	glm::vec3 _position;
};