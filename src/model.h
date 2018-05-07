#pragma once

#include <string>
#include <vector>
#include <assimp\scene.h>
#include <unordered_map>
#include "Material.h"
#include "mesh.h"

class Shader;

class Model 
{
public:
	Model(const std::string& path);
	void draw(const Shader& shader);

private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	Texture Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName);

private:
	std::vector<Mesh> _meshes;
	std::string _directory;
};