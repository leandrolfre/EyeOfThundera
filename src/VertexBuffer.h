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
	VertexBuffer(std::vector<Vertex>&& vertexList, std::vector<unsigned int>&& indices);
	~VertexBuffer();
	int vertexBufferSize() { return _vertices.size() * sizeof(Vertex); }
	int indexBufferSize() { return _indices.size() * sizeof(unsigned int); }
	const std::vector<Vertex>& vertexData() { return _vertices; }
	const std::vector<unsigned int>& indexData() { return _indices; }
	bool hasPositions;
	bool hasNormals;
	bool hasTexCoords;
private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
};