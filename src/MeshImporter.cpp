#include "MeshImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include "Geometry.h"
#include "Material.h"
#include "VertexBuffer.h"
#include "Technique.h"
#include "Pass.h"
#include "Shader.h"
#include "RenderState.h"


void MeshImporter::load(const std::string& path) 
{
	if (!_importer) 
	{
		_importer.reset(new Assimp::Importer());
	}
	_currentScene = _importer->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
}

MeshImporter::MeshImporter()
{
}

MeshImporter::~MeshImporter()
{
}

std::vector<GeometryUPtr> MeshImporter::getMeshes()
 {
	 if (!_currentScene || _currentScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_currentScene->mRootNode)
	 {
		 std::cout << "ASSIMP ERROR: " << _importer->GetErrorString() << std::endl;
		 return std::vector<GeometryUPtr>();
	 }
	 
	 auto node = _currentScene->mRootNode;
	 std::vector<GeometryUPtr> geometries(node->mNumChildren);
	 
	 for (int i = 0; i < node->mNumChildren; i++)
	 {
		auto currentChild = node->mChildren[i];
		aiMesh* mesh = _currentScene->mMeshes[currentChild->mMeshes[0]];
		
		auto geometry = new Geometry(createVertexBuffer(mesh));
		//geometry->setMaterial(createMaterial(mesh));
		geometries.emplace_back(geometry);

	 }

	 return geometries;
 }

 std::unique_ptr<VertexBuffer> MeshImporter::createVertexBuffer(aiMesh* mesh)
{
	std::vector<Vertex> verts;
	verts.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		auto v = mesh->mVertices[i];
		auto n = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D(0.0f);
		auto t = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0] : &aiVector3D(0.0f);
		Vertex vertex;
		vertex.position = glm::vec3(v.x, v.y, v.z);
		vertex.normal = glm::vec3(n.x, n.y, n.z);
		vertex.texCoord = glm::vec2(t[i].x, t[i].y);
		verts.push_back(std::move(vertex));
	}

	std::vector<unsigned int> indx;
	indx.reserve(mesh->mNumFaces * 3);
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		auto face = mesh->mFaces[i];
		indx.insert(indx.cbegin() + i * face.mNumIndices, &face.mIndices[0], &face.mIndices[0] + face.mNumIndices);
	}
	
	auto vertexBuffer = new VertexBuffer(std::move(verts), std::move(indx));
	vertexBuffer->hasPositions = mesh->HasPositions();
	vertexBuffer->hasNormals = mesh->HasNormals();
	vertexBuffer->hasTexCoords = mesh->HasTextureCoords(0);
	return std::unique_ptr<VertexBuffer>(vertexBuffer);
}

 std::unique_ptr<Material> MeshImporter::createMaterial(aiMesh* mesh) 
 {
	 auto material = new Material();

	return MaterialUPtr(material);
 }

//Texture Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName)
//{
//	aiString str;
//	material->GetTexture(type, 0, &str);
//	Texture texture;
//
//	std::string path("");
//	if (str.length > 0)
//	{
//		path = _directory + str.C_Str();
//	}
//	/*else
//	{
//		path = "assets/default/white.png";
//	}*/
//
//	texture.id = TextureManager::getInstance().loadTexture(path);
//	texture.type = typeName;
//	texture.path = path;
//	return texture;
//}