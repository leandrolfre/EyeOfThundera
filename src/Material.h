#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Technique;

using TechniqueUPtr = std::unique_ptr<Technique>;
class Material 
{
public:
	Material();
	~Material();
	void addTechnique(TechniqueUPtr t);
	Technique* getTechnique(const std::string& name);
private:
	std::string _name;
	std::unordered_map<std::string, TechniqueUPtr> _techniques;
	Technique* _currentTechnique;
};