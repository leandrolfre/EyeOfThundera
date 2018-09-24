#include "Renderer.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

Renderer::Renderer(int width, int height) : _width(width), _height(height)
{

}

void Renderer::initSystem() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
	_activeBuffers = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
	glClear(_activeBuffers);
}

void Renderer::enableBuffer(int buffer) 
{
	if (!(_activeBuffers & buffer))
	{
		glEnable(buffer);
		_activeBuffers |= buffer;
	}
}

void Renderer::disableBuffer(int buffer) 
{
	if (_activeBuffers & buffer)
	{
		glDisable(buffer);
		_activeBuffers ^= buffer;
	}
}

void Renderer::enableDepth() 
{
	enableBuffer(GL_DEPTH_TEST);
}

void Renderer::disableDepth() 
{
	disableBuffer(GL_DEPTH_TEST);
}

void Renderer::enableStencil()
{
	enableBuffer(GL_STENCIL_TEST);
}

void Renderer::disableStencil()
{
	disableBuffer(GL_STENCIL_TEST);
}

void Renderer::enableCullFace() 
{
	glEnable(GL_CULL_FACE);
}

void Renderer::disableCullFace()
{
	glDisable(GL_CULL_FACE);
}

void Renderer::enableMultiSample() 
{
	glEnable(GL_MULTISAMPLE);
}

void Renderer::disableMultiSample() 
{
	glDisable(GL_MULTISAMPLE);
}

void Renderer::clearActiveBuffers() 
{
	glClear(_activeBuffers);
}

void Renderer::setCamera(Camera* camera) 
{
	_activeCamera = camera;
}

Camera* Renderer::getCamera() 
{
	return _activeCamera;
}