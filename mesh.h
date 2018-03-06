#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoord;
};

struct Texture 
{
	unsigned int id;
	std::string type;
};

class Mesh
{

public:
	Mesh() {}
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void draw(Shader )
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
};