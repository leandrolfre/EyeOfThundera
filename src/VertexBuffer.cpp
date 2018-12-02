#include "VertexBuffer.h"
#include "Bindable.h"

VertexBuffer::VertexBuffer(std::vector<Vertex>&& vertexList, std::vector<unsigned int>&& indices) :
	_vertices(vertexList), _indices(indices), hasPositions(false), hasNormals(false), hasTexCoords(false)
{}

VertexBuffer::~VertexBuffer() 
{}