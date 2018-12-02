#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Assimp 
{
	class Importer;
}

class Geometry;
class VertexBuffer;
class Material;
struct aiScene;
struct aiNode;
struct aiMesh;

using GeometryUPtr = std::unique_ptr<Geometry>;
using ImporterUPtr = std::unique_ptr<Assimp::Importer>;

class MeshImporter 
{
public:
	MeshImporter();
	~MeshImporter();
	std::vector<GeometryUPtr> getMeshes();
	void load(const std::string& path);
private:
	std::unique_ptr<VertexBuffer> createVertexBuffer(aiMesh* mesh);
	std::unique_ptr<Material> createMaterial(aiMesh* mesh);
	ImporterUPtr _importer;
	const aiScene* _currentScene;
};