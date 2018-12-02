#pragma once

#include <memory>

class RenderState;
class Program;

using RenderStateUPtr = std::unique_ptr<RenderState>;
using ProgramUPtr = std::unique_ptr<Program>;

class Pass 
{
public:
	Pass();
	~Pass();
private:
	std::unique_ptr<RenderState> _renderState;
	std::unique_ptr<Program> _program;
};