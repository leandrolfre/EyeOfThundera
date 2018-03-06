#pragma once

#include <string>
#include <vector>
#include <assimp\scene.h>
#include "mesh.h"
#include <unordered_map>

class Shader;
class Mesh;

class Model 
{
public:
	Model(const std::string& path);
	void draw(Shader shader);

private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName);
	unsigned int loadTexture(const std::string& textureName);

private:
	std::vector<Mesh> _meshes;
	std::string _directory;
	std::unordered_map<std::string, bool> _textureCache;
};