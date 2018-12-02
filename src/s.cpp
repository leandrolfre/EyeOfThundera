#include "MeshImporter.h"
#include <iostream>
#include <ass
#include "Geometry.h"
//#include "VertexBuffer.h"


void MeshImporter::load(const std::string& path) 
{
	//_importer = std::unique_ptr<Assimp::Importer>(new Assimp::Importer());
	//_currentScene = _importer->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
}

 GeometryUPtr MeshImporter::getMesh(const std::string & meshName)
{
	 if (!_currentScene || _currentScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_currentScene->mRootNode)
	 {
		 //std::cout << "ASSIMP ERROR: " << _importer->GetErrorString() << std::endl;
		 return nullptr;
	 }

	//processNode(scene->mRootNode, scene);
	auto node = _currentScene->mRootNode->FindNode("meshName");
	return GeometryUPtr(new Geometry());
}

 std::vector<GeometryUPtr> MeshImporter::getMeshes() 
 {
	 return std::vector<GeometryUPtr>();
 }

//void MeshImporter::processNode(aiNode * node, const aiScene * scene)
//{
//	for (int i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		//_meshes.push_back(processMesh(mesh, scene));
//	}
//
//	for (int i = 0; i < node->mNumChildren; i++)
//	{
//		processNode(node->mChildren[i], scene);
//	}
//}
//
//Geometry MeshImporter::processMesh(aiMesh * mesh, const aiScene * scene)
//{
//	Geometry currentMesh;
//	std::vector<Vertex> vertices;
//	std::vector<unsigned int> indices;
//
//	for (int i = 0; i < mesh->mNumVertices; i++)
//	{
//		auto v = mesh->mVertices[i];
//		auto n = mesh->mNormals ? mesh->mNormals[i] : aiVector3D(0.0f);
//		auto t = mesh->mTextureCoords[0];
//		Vertex vertex;
//		vertex.position = glm::vec3(v.x, v.y, v.z);
//		vertex.normal = glm::vec3(n.x, n.y, n.z);
//		vertex.texCoord = t ? glm::vec2(t[i].x, t[i].y) : vertex.texCoord = glm::vec2(0.0f, 0.0f);
//		vertices.push_back(vertex);
//	}
//	currentMesh.setVertices(vertices);
//	auto chunk = indices.begin();
//	for (int i = 0; i < mesh->mNumFaces; i++)
//	{
//		auto face = mesh->mFaces[i];
//		indices.insert(chunk, &face.mIndices[0], &face.mIndices[0] + face.mNumIndices);
//		chunk = indices.end();
//	}
//
//	currentMesh.setIndices(indices);
//	if (mesh->mMaterialIndex >= 0)
//	{
//		auto mat = std::unique_ptr<Material>(new Material());
//		auto material = scene->mMaterials[mesh->mMaterialIndex];
//
//		aiColor3D ka(1.f, 1.f, 1.f);
//		aiColor3D kd(1.f, 1.f, 1.f);
//		aiColor3D ks(1.f, 1.f, 1.f);
//		float shininess = 0.0f;
//		material->Get(AI_MATKEY_COLOR_AMBIENT, ka);
//		material->Get(AI_MATKEY_COLOR_DIFFUSE, kd);
//		material->Get(AI_MATKEY_COLOR_SPECULAR, ks);
//		material->Get(AI_MATKEY_SHININESS, shininess);
//
//		mat->shininess = shininess >= 0.01f ? shininess : 32.0f;
//
//		mat->ka = glm::vec3(ka.r, ka.g, ka.b);
//		mat->kd = glm::vec3(kd.r, kd.g, kd.b);
//		mat->ks = glm::vec3(ks.r, ks.g, ks.b);
//
//		mat->diffuseMap = loadMaterialTexture(material, aiTextureType_DIFFUSE, "diffuse");
//		mat->specularMap = loadMaterialTexture(material, aiTextureType_SPECULAR, "specular");
//		currentMesh.setMaterial(std::move(mat));
//	}
//	currentMesh.init();
//	return currentMesh;
//}
//
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