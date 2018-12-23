#include "ProgramManager.h"
#include "Program.h"

ProgramManager& ProgramManager::getInstance()
{
	static ProgramManager _instance;
	return _instance;
}

void ProgramManager::addProgram(ProgramUPtr program, const std::string & key)
{
	_programCache[key] = std::move(program);
}

Program* ProgramManager::getProgram(const std::string & key)
{
	return _programCache[key].get();
}
