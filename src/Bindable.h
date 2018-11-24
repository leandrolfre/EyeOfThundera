#pragma once

#include <memory>

class ResourceIdentifier;

class Bindable 
{
public:
	Bindable() = default;
	virtual ~Bindable() = default;
	ResourceIdentifier* getIdentifier() { return _identifier.get(); }
private:
	std::unique_ptr<ResourceIdentifier> _identifier;
};