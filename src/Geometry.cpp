#include "Geometry.h"
#include "Material.h"
#include "VertexBuffer.h"
#include "BoundingVolume.h"

Geometry::Geometry()
{
}

Geometry::Geometry(VertexBufferUPtr vb) : _vBuffer(std::move(vb))
{
}

Geometry::~Geometry()
{
}

VertexBuffer* Geometry::getVertexBuffer() 
{ 
	return _vBuffer.get(); 
}

Material* Geometry::getMaterial() 
{ 
	return _material.get(); 
}

void Geometry::setMaterial(MaterialUPtr mat) 
{ 
	_material = std::move(mat);
}