#pragma once

#include <string>
#include <vector>

class Pass;

class Technique 
{
public:
	Technique() = default;
	~Technique() = default;
private:
	std::string _name;
	std::vector<Pass> _passes;
};