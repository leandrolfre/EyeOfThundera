#pragma once

#include <memory>

class VertexBuffer;
class BoundingVolume;
class Material;

using VertexBufferUPtr = std::unique_ptr<VertexBuffer>;
using MaterialUPtr = std::unique_ptr<Material>;

class Geometry 
{
public:
	Geometry();
	Geometry(VertexBufferUPtr vb);
	~Geometry();
	VertexBuffer* getVertexBuffer() { return _vBuffer.get(); }
	Material* getMaterial() { return _material.get(); }
	void setMaterial(MaterialUPtr mat) { _material = std::move(mat); }
private:
	MaterialUPtr _material;
	std::unique_ptr<BoundingVolume> _boundingVolume;
	VertexBufferUPtr _vBuffer;
};