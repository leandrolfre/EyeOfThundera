#pragma once

#include "Bindable.h"
#include <vector>
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class VertexBuffer : public Bindable
{
public:
	VertexBuffer() = default;
	~VertexBuffer() = default;
private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
};