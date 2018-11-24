#pragma once

#include <string>
#include <vector>

class Technique;

class Material 
{
public:
	Material() = default;
private:
	std::string _name;
	std::vector<Technique> _techniques;
	Technique* _currentTechnique;
};