#pragma once

class ResourceIdentifier 
{
public:
	ResourceIdentifier(int id) : _id(id) {}
	~ResourceIdentifier() {}
	int getID() { return _id; }
private:
	int _id;
};