#pragma once

#include <memory>
#include <string>
#include <vector>

class Pass;

using PassUPtr = std::unique_ptr<Pass>;

class Technique 
{
public:
	Technique();
	~Technique();
private:
	std::string _name;
	std::vector<PassUPtr> _passes;
};