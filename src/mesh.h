#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Shader;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture 
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{

public:
	Mesh() {}
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void draw(Shader shader);
private:
	void init();
public:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	std::vector<Texture> _textures;

private:
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;
	
};