#include "Technique.h"
#include "Pass.h"

Technique::Technique()
{
}

Technique::Technique(std::string&& name) : _name(std::move(name))
{
}

Technique::~Technique()
{
}

std::string Technique::getName()
{
	return _name;
}

void Technique::addPass(PassUPtr p)
{
	_passes.push_back(p);
}

Pass * Technique::getPass(int i)
{
	if (i < _passes.size() && _passes[i]) 
	{
		return _passes[i].get();
	}

	return nullptr;
}
