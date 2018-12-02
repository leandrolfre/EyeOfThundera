#pragma once

#include <memory>
#include "ResourceIdentifier.h"

using ResourceIdUPtr = std::unique_ptr<ResourceIdentifier>;

class Bindable 
{
public:
	Bindable();
	virtual ~Bindable();
	ResourceIdentifier* getIdentifier() { return _identifier.get(); }
	void setIdentifier(ResourceIdUPtr resId) { _identifier = std::move(resId); }
private:
	ResourceIdUPtr _identifier;
};