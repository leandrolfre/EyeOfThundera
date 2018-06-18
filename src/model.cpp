#include "model.h"
#include "shader.hpp"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include "TextureManager.h"
#include <memory>
#include <glm\gtc\type_ptr.hpp>

Model::Model(const std::string& path) : _scale(1.0f)
{
	loadModel(path);
}

void Model::draw(const Shader& shader)
{
	for (int i = 0; i < _meshes.size(); i++) 
	{
		_meshes[i].draw(shader);
	}
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cout << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
		return;
	}

	_directory = path.substr(0, path.find_last_of('/')+1);
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for (int i = 0; i < node->mNumMeshes; i++) 
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];	
		_meshes.push_back(processMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++) 
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	Mesh currentMesh;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < mesh->mNumVertices; i++) 
	{
		auto v = mesh->mVertices[i];
		auto n = mesh->mNormals ? mesh->mNormals[i] : aiVector3D(0.0f);
		auto t = mesh->mTextureCoords[0];
		Vertex vertex;
		vertex.position = glm::vec3(v.x, v.y, v.z);
		vertex.normal = glm::vec3(n.x, n.y, n.z);
		vertex.texCoord =  t ? glm::vec2(t[i].x, t[i].y) : vertex.texCoord = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	currentMesh.setVertices(vertices);
	auto chunk = indices.begin();
	for (int i = 0; i < mesh->mNumFaces; i++) 
	{
		auto face = mesh->mFaces[i];
		indices.insert(chunk, &face.mIndices[0], &face.mIndices[0] + face.mNumIndices);
		chunk = indices.end();
	}
	
	currentMesh.setIndices(indices);
	if (mesh->mMaterialIndex >= 0) 
	{
		auto mat = std::unique_ptr<Material>(new Material());
		auto material = scene->mMaterials[mesh->mMaterialIndex];

		aiColor3D ka(1.f, 1.f, 1.f);
		aiColor3D kd(1.f, 1.f, 1.f);
		aiColor3D ks(1.f, 1.f, 1.f);
		float shininess = 0.0f;
		material->Get(AI_MATKEY_COLOR_AMBIENT, ka);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, kd);
		material->Get(AI_MATKEY_COLOR_SPECULAR, ks);
		material->Get(AI_MATKEY_SHININESS, shininess);

		mat->shininess = shininess >= 0.01f ? shininess : 32.0f;

		mat->ka = glm::vec3(ka.r, ka.g, ka.b);
		mat->kd = glm::vec3(kd.r, kd.g, kd.b);
		mat->ks = glm::vec3(ks.r, ks.g, ks.b);

		mat->diffuseMap = loadMaterialTexture(material, aiTextureType_DIFFUSE, "diffuse");
		mat->specularMap = loadMaterialTexture(material, aiTextureType_SPECULAR, "specular");
		currentMesh.setMaterial(std::move(mat));
	}
	currentMesh.init();
	return currentMesh;
}

Texture Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName)
{
	aiString str;
	material->GetTexture(type, 0, &str);
	Texture texture;

	std::string path("");
	if (str.length > 0)
	{
		path = _directory + str.C_Str();
	}
	/*else 
	{
		path = "assets/default/white.png";
	}*/
	
	texture.id = TextureManager::getInstance().loadTexture(path);
	texture.type = typeName;
	texture.path = path;
	return texture;
}

void Model::setPosition(glm::vec3 pos) 
{ 
	_position = pos;
	_model = glm::scale(glm::mat4(1.0f), _scale);
	_model = glm::translate(_model, pos); 
}

void Model::setScale(float scale) 
{ 
	_scale = glm::vec3(scale);
	_model = glm::scale(glm::mat4(1.0f), _scale);
	_model = glm::translate(_model, _position);
}

void Model::rotate(glm::vec3 axis, float angle)
{
	_model = glm::rotate(_model, angle, axis);
}
