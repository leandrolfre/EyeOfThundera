#pragma once

class Spatial 
{
public:
	virtual ~Spatial() = default;
	Spatial* getParent();
	void setParent(Spatial* spatial);
protected:
	Spatial() = default;
	Spatial* _parent;
};