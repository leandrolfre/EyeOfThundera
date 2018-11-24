#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

class Shader;
class Material;



class Mesh
{

public:
	Mesh() = default;
	void draw(const Shader& shader);
	void setVertices(std::vector<Vertex>);
	void setIndices(std::vector<unsigned int>);
	void setMaterial(std::unique_ptr<Material>);
	void init();

	
};