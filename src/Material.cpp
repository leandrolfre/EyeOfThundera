#include "Material.h"
#include "Technique.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::addTechnique(TechniqueUPtr t)
{
	_techniques[t->getName()] = std::move(t);
}

Technique * Material::getTechnique(const std::string & name)
{
	if (_techniques.find(name) != _techniques.end())
	{
		return _techniques[name].get();
	}

	return nullptr;
}
