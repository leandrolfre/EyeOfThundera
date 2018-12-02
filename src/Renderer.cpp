#include "Renderer.h"
#include <glad\glad.h>
#include "Bindable.h"
#include "camera.hpp"
#include "ResourceIdentifier.h"
#include "Geometry.h"
#include "Program.h"
#include "Texture.h"
#include "VertexBuffer.h"
//#include "VisibleSet.h"
#include "Spatial.h"
#include "Material.h"

Renderer::Renderer(int width, int height) : _width(width), _height(height)
{
}

Renderer::~Renderer()
{
}

bool Renderer::initSystem(LoadProc proc) const
{
	return gladLoadGLLoader(proc);
}


void Renderer::setCamera(Camera* camera) 
{
	_activeCamera = camera;
}

Camera* Renderer::getCamera() 
{
	return _activeCamera;
}

//Temporary
void Renderer::drawScene(std::vector<std::unique_ptr<Geometry>>& visibleSet)
{
	//Handle here different rendering path(forward, deferred)
	//also post processing
	for (int i = 0; i < visibleSet.size(); i++)
	{
		draw(visibleSet[i].get());
	}
}

//void Renderer::drawScene(VisibleSet& visibleSet) 
//{
//	//Handle here different rendering path(forward, deferred)
//	//also post processing
//}

void Renderer::draw(Geometry* geometry) 
{
	//temporary ogl code
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);

	////TODO: Here setGlobalState receive a list of states(Alpha, Cull, Stencil...). Use an Wrapper GlobalState instead.
	//setGlobalState(geometry->states);
	setWorldTransformation();
	auto vb = geometry->getVertexBuffer();
	enableVertexBuffer(vb);

	applyMaterial(geometry->getMaterial());

	disableVertexBuffer();
	//restoreWorldTransformation();
	////restoreGlobalState();
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

void Renderer::applyMaterial(Material* mat) 
{
	//for (int pass; pass < effect->numPass; ++pass) 
	//{
	//	//effect->loadPrograms(pass);
	//	effect->setGlobalState(pass, this, primaryEffect);

	//	//TODO: Make VertexProgram and PixelProgram into Program
	//	VertexProgram* vProgram = effect->getVProgram(pass);
	//	enableVertexProgram(vProgram);

	//	PixelProgram* pProgram= effect->getPProgram();
	//	enablePixelProgram(pProgram);

	//	//enable/setup textures

	//	//load vertexAttributes

	//	drawElements();

	//	//disable resources (program, textures...)

	//	//effect->restoreGlobalState();
	//}

	//primaryEffect = false;
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

void Renderer::loadResources(Material* mat)
{
}

void Renderer::releaseResources(Material* material)
{
}

void Renderer::loadProgram(Program* program)
{
	ResourceIdentifier* rID = program->getIdentifier();
	if (!rID) 
	{
		onLoadProgram(program);
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

void Renderer::onLoadProgram(Program * vertexProgram)
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
		onLoadTexture(texture);
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

void Renderer::onLoadTexture(Texture * texture)
{
}

void Renderer::onReleaseTexture(ResourceIdentifier * identifier)
{
}

void Renderer::enableVertexBuffer(VertexBuffer* vBuffer)
{
	loadVertexBuffer(vBuffer);
	glBindVertexArray(vBuffer->getIdentifier()->getID());
}

void Renderer::loadVertexBuffer(VertexBuffer * vBuffer)
{
	ResourceIdentifier* id = vBuffer->getIdentifier();
	if (!id)
	{
		onLoadVertexBuffer(vBuffer);
	}
}

void Renderer::onLoadVertexBuffer(VertexBuffer* vertexBuffer)
{
	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexBuffer->vertexBufferSize(), &vertexBuffer->vertexData()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer->indexBufferSize(), &vertexBuffer->indexData()[0], GL_STATIC_DRAW);

	//vertex position
	if (vertexBuffer->hasPositions)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}

	//vertex normal
	if (vertexBuffer->hasNormals)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	}

	//vertex texture coords
	if (vertexBuffer->hasTexCoords)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	}

	glBindVertexArray(0);

	vertexBuffer->setIdentifier(ResourceIdUPtr(new ResourceIdentifier(vao)));

}

void Renderer::disableVertexBuffer()
{
	onReleaseVertexBuffer();
}

void Renderer::onReleaseVertexBuffer()
{
	glBindVertexArray(0);
}
