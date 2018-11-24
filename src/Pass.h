#pragma once

#include <memory>

class RenderState;
class Program;

class Pass 
{
public:
	Pass() = default;
	~Pass() = default;
private:
	std::unique_ptr<RenderState> _renderState;
	std::unique_ptr<Program> _program;
};