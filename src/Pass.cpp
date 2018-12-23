#include "Pass.h"
#include "Program.h"
#include "RenderState.h"

Pass::Pass()
{
}

Pass::~Pass()
{
}

void Pass::setProgram(Program * program)
{
	_program = program;
}

Program* Pass::getProgram()
{
	return _program;
}