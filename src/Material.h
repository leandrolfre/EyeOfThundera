#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Technique;
class Pass;

using TechniqueUPtr = std::unique_ptr<Technique>;
class Material 
{
public:
	Material();
	~Material();
	void addTechnique(TechniqueUPtr t);
	Technique* getTechnique(const std::string& name);
    int numPasses();
    Pass* getPass(int i);
private:
	std::string _name;
	std::unordered_map<std::string, TechniqueUPtr> _techniques;
	Technique* _currentTechnique;
};