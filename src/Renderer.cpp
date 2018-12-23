#include "Renderer.h"
#include <glad\glad.h>
#include "Bindable.h"
#include "camera.hpp"
#include "ResourceIdentifier.h"
#include "Geometry.h"
#include "Program.h"
#include "Sampler.h"
#include "VertexBuffer.h"
//#include "VisibleSet.h"
#include "Spatial.h"
#include "Material.h"
#include <iostream>
#include "TextureManager.h"

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
	}
}

void Renderer::releaseProgram(Bindable * program)
{
	ResourceIdentifier* rID = program->getIdentifier();
	if (rID) 
	{
		onReleaseProgram(rID);
	}
}

void Renderer::enableProgram(Program* program)
{
	loadProgram(program);
	ResourceIdentifier* id = program->getIdentifier();
	glUseProgram(id->getID());
}

void Renderer::disableProgram(Program* program)
{
	releaseProgram(program);
}

void Renderer::onLoadProgram(Program * program)
{
	auto id =  glCreateProgram();
	//Insert builtin uniforms
	//unsigned int lmShader = compileShader(GL_FRAGMENT_SHADER, "lightModels.frag");

	program->setIdentifier(ResourceIdUPtr(new ResourceIdentifier(id)));

	for (int i = 0; i < (int)ShaderType::ShaderTypeMax; ++i) 
	{
		auto shaderId = compileShader((ShaderType)i, program);
		glAttachShader(id, shaderId);
		glDeleteShader(shaderId);
	}
	glLinkProgram(id);
}

void Renderer::onReleaseProgram(ResourceIdentifier * identifier)
{
	glDeleteProgram(identifier->getID());

}

unsigned int Renderer::compileShader(ShaderType type, Program* program) {

	auto shader = 0;

	switch (type)
	{
	case ShaderType::Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::Fragment:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::Geometry:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
	auto shaderSource = program->getShaderByType(type)->source.c_str();
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	checkError(shader);

	return shader;
}

void Renderer::checkError(unsigned int shader) const
{
	int  success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Renderer::loadSampler2D(Sampler2D * sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (!id) 
	{
		onLoadSampler2D(sampler);
	}
}

void Renderer::releaseSampler2D(Bindable * sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (id) 
	{
		onReleaseSampler2D(id);
	}
}

void Renderer::enableSampler2D(Sampler2D* sampler)
{
	loadSampler2D(sampler);
	ResourceIdentifier* id = sampler->getIdentifier();
	glActiveTexture(GL_TEXTURE0 + sampler->unitID);
	glBindTexture(GL_TEXTURE_2D, id->getID());
}

void Renderer::disableSampler2D(Sampler2D* sampler)
{
	if (sampler->getIdentifier())
	{
		releaseSampler2D(sampler);
	}
}

void Renderer::onLoadSampler2D(Sampler2D* sampler)
{
	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, translateWrapMode(sampler->wrapS));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, translateWrapMode(sampler->wrapT));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, translateFilterMode(sampler->minFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, translateFilterMode(sampler->magFilter));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sampler->_texture->width, sampler->_texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sampler->_texture->data);
	if (sampler->generateMipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	sampler->setIdentifier(ResourceIdUPtr(new ResourceIdentifier(textureId)));
}

void Renderer::onReleaseSampler2D(ResourceIdentifier * identifier)
{
}

void Renderer::loadSamplerCube(SamplerCube* sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (!id)
	{
		onLoadSamplerCube(sampler);
	}
}

void Renderer::releaseSamplerCube(Bindable * sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (id)
	{
		onReleaseSamplerCube(id);
	}
}

void Renderer::onLoadSamplerCube(SamplerCube * sampler)
{
	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	for (int i = 0; i < sampler->_textures.size(); ++i)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, translateWrapMode(sampler->wrapS));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, translateWrapMode(sampler->wrapT));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, translateWrapMode(sampler->wrapR));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, translateFilterMode(sampler->minFilter));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, translateFilterMode(sampler->magFilter));
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, sampler->_textures[i]->width, sampler->_textures[i]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sampler->_textures[i]->data);
	}
	if (sampler->generateMipmap)
	{
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}
	sampler->setIdentifier(ResourceIdUPtr(new ResourceIdentifier(textureId)));
}

void Renderer::enableSamplerCube(SamplerCube * sampler)
{
	loadSamplerCube(sampler);
	ResourceIdentifier* id = sampler->getIdentifier();
	glBindTexture(GL_TEXTURE_CUBE_MAP, id->getID());
	glActiveTexture(GL_TEXTURE0 + sampler->unitID);
}

void Renderer::disableSamplerCube(SamplerCube * sampler)
{
	if (sampler->getIdentifier())
	{
		releaseSampler2D(sampler);
	}
}

void Renderer::onReleaseSamplerCube(ResourceIdentifier * identifier)
{
}

GLint Renderer::translateFilterMode(FilterMode mode)
{
	switch (mode)
	{
	case FilterMode::Nearest:
		return GL_NEAREST;
	case FilterMode::Linear:
		return GL_LINEAR;
	case FilterMode::NearestNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case FilterMode::LinearNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case FilterMode::NearestLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case FilterMode::LinearLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		return -1;
	}
}

GLint Renderer::translateWrapMode(WrapMode mode)
{
	switch (mode)
	{
	case WrapMode::Repeat:
		return GL_REPEAT;
	case WrapMode::MirroredRepeat:
		return GL_MIRRORED_REPEAT;
	case WrapMode::ClampToEdge:
		return GL_CLAMP_TO_EDGE;
	case WrapMode::ClamptoBorder:
		return GL_CLAMP_TO_BORDER;
	default:
		return -1;
	}
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
