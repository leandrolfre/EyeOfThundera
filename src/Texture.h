#pragma once

#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture();
	virtual ~Texture();
	unsigned int unitID;
	unsigned char* data;
};