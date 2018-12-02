#pragma once

class ResourceIdentifier 
{
public:
	ResourceIdentifier();
	ResourceIdentifier(int id);
	~ResourceIdentifier();
	int getID() { return _id; }
private:
	int _id;
};