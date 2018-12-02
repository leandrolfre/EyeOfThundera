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
