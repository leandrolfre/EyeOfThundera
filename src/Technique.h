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
	Technique(std::string&& name);
	~Technique();
	std::string getName();
	void addPass(PassUPtr p);
	Pass* getPass(int i);
    int numPasses();
private:
	std::string _name;
	std::vector<PassUPtr> _passes;
};