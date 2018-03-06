#define STB_IMAGE_IMPLEMENTATION
#include "model.h"
#include "shader.hpp"
#include "stb_image.h"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <glad\glad.h>


unsigned int Model::loadTexture(const std::string& textureName)
{

	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &channels, 0);
	GLuint textureId = 0;
	if (data)
	{

		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		glGenTextures(1, &textureId);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	return textureId;
}

Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::draw(Shader shader)
{
	for (int i = 0; i < _meshes.size(); i++) 
	{
		_meshes[i].draw(shader);
	}
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
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
	std::vector<Vertex>	vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

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

	auto chunk = indices.begin();
	for (int i = 0; i < mesh->mNumFaces; i++) 
	{
		auto face = mesh->mFaces[i];
		indices.insert(chunk, &face.mIndices[0], &face.mIndices[0] + face.mNumIndices);
		chunk = indices.end();
	}

	if (mesh->mMaterialIndex >= 0) 
	{
		auto material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (int i = 0; i < material->GetTextureCount(type); i++) 
	{
		aiString str;
		material->GetTexture(type, i, &str);

		if (_textureCache.find(str.data) != _textureCache.end()) 
		{
			continue;
		}

		Texture texture;
		texture.id = loadTexture(_directory + str.C_Str());
		texture.type = typeName;
		texture.path = str.data;
		textures.push_back(texture);
		_textureCache[str.data] = true;
	}
	return textures;
}
