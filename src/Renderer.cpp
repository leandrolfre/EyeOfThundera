#include "Renderer.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "ResourceIdentifier.h"
#include "Program.h"
#include "Texture.h"
#include "VertexBuffer.h"


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
	_currentGeometry = geometry;
	//TODO: Here setGlobalState receive a list of states(Alpha, Cull, Stencil...). Use an Wrapper GlobalState instead.
	setGlobalState(geometry->states);
	setWorldTransformation();

	//TODO: replace this enableIndexBuffer by VAO logic
	enableIndexBuffer();

	bool isPrimaryEffect = true;

	//TODO: Remove this light effect logic
	if (_currentGeometry->lightEffect)
	{
		applyEffect(_currentGeometry->lightEffect, isPrimaryEffect);
	}

	for (int i = 0; i < _currentGeometry->numEffects; ++i) 
	{
		ShaderEffect* effect = _currentGeometry->getEffect(i);
		applyEffect(effect, isPrimaryEffect);
	}

	disableIndexBuffer();
	restoreWorldTransformation();
	//restoreGlobalState();
	_currentGeometry = nullptr;
}

void Renderer::drawElements() 
{
	//add here opengl code to draw
}

void Renderer::setWorldTransformation()
{
}

void Renderer::restoreWorldTransformation()
{
}

void Renderer::applyEffect(ShaderEffect* effect, bool& primaryEffect) 
{
	for (int pass; pass < effect->numPass; ++pass) 
	{
		//effect->loadPrograms(pass);
		effect->setGlobalState(pass, this, primaryEffect);

		//TODO: Make VertexProgram and PixelProgram into Program
		VertexProgram* vProgram = effect->getVProgram(pass);
		enableVertexProgram(vProgram);

		PixelProgram* pProgram= effect->getPProgram();
		enablePixelProgram(pProgram);

		//enable/setup textures

		//load vertexAttributes

		drawElements();

		//disable resources (program, textures...)

		//effect->restoreGlobalState();
	}

	primaryEffect = false;
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

void Renderer::loadProgram(Program* program)
{
	ResourceIdentifier* rID = program->getIdentifier();
	if (!rID) 
	{
		onLoadProgram(rID, program);
		//program->onLoad(this, &releaseVertexProgram, rID);
	}
}

void Renderer::releaseProgram(Bindable * program)
{
	ResourceIdentifier* rID = program->getIdentifier();
	if (rID) 
	{
		onReleaseProgram(rID);
		//program->onRelease(this);
	}
}

void Renderer::enableProgram(Program* program)
{
	loadProgram(program);
	ResourceIdentifier* id = program->getIdentifier();
	//TODO:init resource
	//onEnableProgram();

}

void Renderer::disableProgram(Program* program)
{
	releaseProgram(program);
}

void Renderer::onLoadProgram(ResourceIdentifier * identifier, Program * vertexProgram)
{
	/*VertexProgramID* vpID = new VertexProgramID();
	identifier = vpID;*/
	/*opengl code to generate and bind a program*/
}

void Renderer::onReleaseProgram(ResourceIdentifier * identifier)
{
	/*opengl code to release a program*/
}

void Renderer::loadTexture(Texture * texture)
{
	ResourceIdentifier* id = texture->getIdentifier();
	if (!id) 
	{
		onLoadTexture(id, texture);
	}
}

void Renderer::releaseTexture(Bindable * texture)
{
	ResourceIdentifier* id = texture->getIdentifier();
	if (id) 
	{
		onReleaseTexture(id);
	}
}

void Renderer::enableTexture(Texture* texture)
{
	loadTexture(texture);
	ResourceIdentifier* id = texture->getIdentifier();
}

void Renderer::disableTexture(Texture* texture)
{
	if (texture->getIdentifier())
	{
		releaseTexture(texture);
	}
}

void Renderer::onLoadTexture(ResourceIdentifier * identifier, Texture * texture)
{
}

void Renderer::onReleaseTexture(ResourceIdentifier * identifier)
{
}

void Renderer::loadVertexBuffer(VertexBuffer * vBuffer)
{
	ResourceIdentifier* id = vBuffer->getIdentifier();
	if (!id)
	{
		onLoadVertexBuffer(id, vBuffer);
	}
}

void Renderer::releaseVertexBuffer(Bindable * bindable)
{
}

void Renderer::onLoadVertexBuffer(ResourceIdentifier* identifier, VertexBuffer * vertexBuffer)
{
	/*VertexProgramID* vpID = new VertexProgramID();
	identifier = vpID;*/
	/*opengl code to generate and bind a program*/
}

void Renderer::onReleaseVertexBuffer(ResourceIdentifier* identifier)
{
}

ResourceIdentifier* Renderer::enableVertexBuffer(VertexBuffer* vBuffer)
{
	return nullptr;
}

void Renderer::disableVertexBuffer(ResourceIdentifier* ri)
{
}
