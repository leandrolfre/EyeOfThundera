#pragma once

#include <memory>

class RenderState;
class Program;

using RenderStateUPtr = std::unique_ptr<RenderState>;

class Pass 
{
public:
	Pass();
	~Pass();
private:
	std::unique_ptr<RenderState> _renderState;
	Program* _program;
};