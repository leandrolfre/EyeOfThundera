#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

class Shader;
class Material;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh
{

public:
	Mesh() = default;
	void draw(const Shader& shader);
	void setVertices(std::vector<Vertex>);
	void setIndices(std::vector<unsigned int>);
	void setMaterial(std::unique_ptr<Material>);
	void init();
private:
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	std::unique_ptr<Material> _material;
	
};