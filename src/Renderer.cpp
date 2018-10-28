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

void Renderer::drawScene(VisibleSet& visibleSet) 
{
}

void Renderer::draw(Geometry* geometry) 
{
}

void Renderer::drawElements() 
{
}

void Renderer::applyEffect(ShaderEffect* effect, bool primaryEffect) 
{
}

void Renderer::loadAllResources(Spatial * scene)
{
}

void Renderer::releaseAllResources(Spatial * scene)
{
}

void Renderer::loadResources(Geometry * geometry)
{
}

void Renderer::releaseResources(Geometry * geometry)
{
}

void Renderer::loadResources(ShaderEffect * shaderEffect)
{
}

void Renderer::releaseResources(ShaderEffect * shaderEffect)
{
}

void Renderer::loadVertexProgram(VertexProgram * vertexProgram)
{
	/*ResourceIdentifier* rID = vertexProgram->getIdentifier();
	if (!rID) 
	{
		onLoadVertexProgram(rID, vertexProgram);
		vertexProgram->onLoad(this, &releaseVertexProgram, rID);
	}*/
}

void Renderer::releaseVertexProgram(Bindable * vertexProgram)
{
	/*ResourceIdentifier* rID = vertexProgram->getIdentifier();
	if (rID) 
	{
		onReleaseVertexProgram(rID);
		vertexProgram->onRelease(this);
	}*/
}

void Renderer::loadPixelProgram(PixelProgram * pixelProgram)
{
}

void Renderer::releasePixelProgram(Bindable * pixelProgram)
{
}

void Renderer::loadTexture(Texture * texture)
{
}

void Renderer::releaseTexture(Bindable * texture)
{
}

void Renderer::loadVertexBuffer(int pass, const Attributes & attr, VertexBuffer * vBuffer)
{
}

void Renderer::releaseVertexBuffer(int pass, Bindable * bindable)
{
}

void Renderer::loadIndexBuffer(IndexBuffer * indexBuffer)
{
}

void Renderer::releaseIndexBuffer(Bindable * bindable)
{
}

void Renderer::onLoadVertexProgram(ResourceIdentifier * identifier, VertexProgram * vertexProgram)
{
	/*VertexProgramID* vpID = new VertexProgramID();
	identifier = vpID;*/
	/*opengl code to generate and bind a program*/
}

void Renderer::onReleaseVertexProgram(ResourceIdentifier * identifier)
{
	/*opengl code to release a program*/
}

void Renderer::onLoadPixelProgram(ResourceIdentifier * identifier, PixelProgram * pixelProgram)
{
}

void Renderer::onReleasePixelProgram(ResourceIdentifier * identifier)
{
}

void Renderer::onLoadTexture(ResourceIdentifier * identifier, Texture * texture)
{
}

void Renderer::onReleaseTexture(ResourceIdentifier * identifier)
{
}

void Renderer::onLoadVertexBuffer(ResourceIdentifier * identifier, const Attributes & attr, VertexBuffer * vertexBuffer)
{
}

void Renderer::onReleaseVertexBuffer(ResourceIdentifier * identifier)
{
}

void Renderer::onLoadIndexBuffer(ResourceIdentifier * identifier, IndexBuffer * vertexBuffer)
{
}

void Renderer::onReleaseIndexBuffer(ResourceIdentifier * identifier)
{
}
