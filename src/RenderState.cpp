#include "RenderState.h"
#include <glad\glad.h>

void RenderState::init() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Global State
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
	_activeBuffers = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
	glClear(_activeBuffers);
}

void RenderState::enableDepth()
{
	enableBuffer(GL_DEPTH_TEST);
}

void RenderState::disableDepth()
{
	disableBuffer(GL_DEPTH_TEST);
}

void RenderState::enableStencil()
{
	enableBuffer(GL_STENCIL_TEST);
}

void RenderState::disableStencil()
{
	disableBuffer(GL_STENCIL_TEST);
}

void RenderState::enableCullFace()
{
	glEnable(GL_CULL_FACE);
}

void RenderState::disableCullFace()
{
	glDisable(GL_CULL_FACE);
}

void RenderState::enableMultiSample()
{
	glEnable(GL_MULTISAMPLE);
}

void RenderState::disableMultiSample()
{
	glDisable(GL_MULTISAMPLE);
}

void RenderState::clearActiveBuffers()
{
	glClear(_activeBuffers);
}

void RenderState::enableBuffer(int buffer)
{
	if (!(_activeBuffers & buffer))
	{
		glEnable(buffer);
		_activeBuffers |= buffer;
	}
}

void RenderState::disableBuffer(int buffer)
{
	if (_activeBuffers & buffer)
	{
		glDisable(buffer);
		_activeBuffers ^= buffer;
	}
}