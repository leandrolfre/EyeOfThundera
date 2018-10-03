#include "Spatial.h"

Spatial * Spatial::getParent()
{
	return _parent;
}

void Spatial::setParent(Spatial * spatial)
{
	_parent = spatial;
}
