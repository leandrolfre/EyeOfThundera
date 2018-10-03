#pragma once

#include <vector>
#include "Spatial.h"

class Node : public Spatial
{
public:
	Node() = default;
	virtual ~Node() = default;
	int getQuantity() const;
	int attachChild(Spatial* child);
	int detachChild(Spatial* child);
	Spatial* detachChildAt(int i);
	Spatial setChild(int i, Spatial* child);
	Spatial* getChild(int i);
protected:
	std::vector<Spatial*> _children;
};
