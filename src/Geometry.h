#pragma once

#include <memory>

class Material;
class BoundingVolume;
class VertexBuffer;

class Geometry 
{
public:
	Geometry() = default;
	virtual ~Geometry() = default;
private:
	std::unique_ptr<Material> _material;
	std::unique_ptr<BoundingVolume> _boundingVolume;
	std::unique_ptr<VertexBuffer> _buffer;
};