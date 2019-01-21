#include "Renderer.h"
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
#include "UniformAttribute.h"
#include "RenderState.h"
#include "Pass.h"

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
    int numPasses = mat->numPasses();
	for (int i; i < numPasses; ++i) 
	{
        auto pass = mat->getPass(i);
        auto& renderState = pass->getRenderState();
        loadRenderState(renderState.get());
		//effect->loadPrograms(pass);
		//effect->setGlobalState(pass, this, primaryEffect);

		//TODO: Make VertexProgram and PixelProgram into Program
		/*VertexProgram* vProgram = effect->getVProgram(pass);
		enableVertexProgram(vProgram);

		PixelProgram* pProgram= effect->getPProgram();
		enablePixelProgram(pProgram);*/

		//enable/setup textures
     /*set builtin uniforms
     set user defined uniforms*/
		//load vertexAttributes

		drawElements();

		//disable resources (program, textures...)

		//effect->restoreGlobalState();
	}

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
	//unsigned int lmShader = compileShader(GL_FRAGMENT_SHADER, "lightModels.frag");

	program->setIdentifier(ResourceIdUPtr(new ResourceIdentifier(id)));

	for (int i = 0; i < (int)ShaderType::ShaderTypeMax; ++i) 
	{
		auto shaderId = compileShader((ShaderType)i, program);
		glAttachShader(id, shaderId);
		glDeleteShader(shaderId);
	}
	glLinkProgram(id);

    GLint activeUniforms;
    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &activeUniforms);
    if (activeUniforms > 0)
    {
        GLint length;
        glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
        if (length > 0)
        {
            for (int i = 0; i < activeUniforms; ++i)
            {
                GLint size;
                GLenum type;
                char* uniformName;
                glGetActiveUniform(id, i, length, nullptr, &size, &type, uniformName);
                auto uniform = program->getUniformByName(uniformName);
                uniform->location = glGetUniformLocation(id, uniformName);
                uniform->type = type;
            }
        }
    }
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

void Renderer::loadSampler(Sampler2D * sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (!id) 
	{
		onLoadSampler(sampler);
	}
}

void Renderer::enableSampler(Sampler2D* sampler)
{
	loadSampler(sampler);
	ResourceIdentifier* id = sampler->getIdentifier();
	glActiveTexture(GL_TEXTURE0 + sampler->unitID);
	glBindTexture(GL_TEXTURE_2D, id->getID());
}

void Renderer::disableSampler(Sampler2D* sampler)
{
	if (sampler->getIdentifier())
	{
		releaseSampler(sampler);
	}
}

void Renderer::onLoadSampler(Sampler2D* sampler)
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

void Renderer::loadSampler(SamplerCube* sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (!id)
	{
		onLoadSampler(sampler);
	}
}

void Renderer::releaseSampler(Bindable * sampler)
{
	ResourceIdentifier* id = sampler->getIdentifier();
	if (id)
	{
		onReleaseSampler(id);
	}
}

void Renderer::onLoadSampler(SamplerCube * sampler)
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

void Renderer::enableSampler(SamplerCube * sampler)
{
	loadSampler(sampler);
	ResourceIdentifier* id = sampler->getIdentifier();
	glBindTexture(GL_TEXTURE_CUBE_MAP, id->getID());
	glActiveTexture(GL_TEXTURE0 + sampler->unitID);
}

void Renderer::disableSampler(SamplerCube * sampler)
{
	if (sampler->getIdentifier())
	{
		releaseSampler(sampler);
	}
}

void Renderer::loadRenderState(RenderState* renderState)
{
    _currentBufferMask = GL_COLOR_BUFFER_BIT;
    if (renderState->Depth.enable) 
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(translateFuncEnum(renderState->Depth.func));
        glDepthMask((renderState->Depth.depthMask ? GL_TRUE : GL_FALSE));
        _currentBufferMask |= GL_DEPTH_BUFFER_BIT;
    }
    else 
    {
        glDisable(GL_DEPTH_TEST);
    }

    if (renderState->Blend.enable)
    {
        glEnable(GL_BLEND);
        glBlendFunc(translateBlendMode(renderState->Blend.blendSrc), translateBlendMode(renderState->Blend.blendDst));
    }
    else 
    {
        glDisable(GL_BLEND);
    }

    if (renderState->Stencil.enable)
    {
        glEnable(GL_STENCIL_TEST);
        loadStencil(renderState->Stencil);
        _currentBufferMask |= GL_STENCIL_BUFFER_BIT;
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }

    if (renderState->CullFace.enable)
    {
        glEnable(GL_CULL_FACE);
        loadCullFace(renderState->CullFace);
    }
}

auto Renderer::translateFuncEnum(Func func) -> GLenum
{
    switch (func)
    {
    case Func::ALWAYS:
        return GL_ALWAYS;
    case Func::NEVER:
        return GL_NEVER;
    case Func::LESS:
        return GL_LESS;
    case Func::EQUAL:
        return GL_EQUAL;
    case Func::LESS_EQUAL:
        return GL_LEQUAL;
    case Func::GREATER:
        return GL_GREATER;
    case Func::NOT_EQUAL:
        return GL_NOTEQUAL;
    case Func::GREATER_EQUAL:
        return GL_GEQUAL;
    }
}

auto Renderer::translateBlendMode(BlendMode mode)->GLenum
{
    switch (mode)
    {
    case BlendMode::ZERO:
        return GL_ZERO;
    case BlendMode::ONE:
        return GL_ONE;
    case BlendMode::SRC_COLOR:
        return GL_SRC_COLOR;
    case BlendMode::ONE_MINUS_SRC_COLOR:
        return GL_ONE_MINUS_SRC_COLOR;
    case BlendMode::DST_COLOR:
        return GL_DST_COLOR;
    case BlendMode::ONE_MINUS_DST_COLOR:
        return GL_ONE_MINUS_DST_COLOR;
    case BlendMode::SRC_ALPHA:
        return GL_SRC_ALPHA;
    case BlendMode::ONE_MINUS_SRC_ALPHA:
        return GL_ONE_MINUS_SRC_ALPHA;
    case BlendMode::DST_ALPHA:
        return GL_DST_ALPHA;
    case BlendMode::ONE_MINUS_DST_ALPHA:
        return GL_ONE_MINUS_DST_ALPHA;
    case BlendMode::CONSTANT_COLOR:
        return GL_CONSTANT_COLOR;
    case BlendMode::ONE_MINUS_CONSTANT_COLOR:
        return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendMode::CONSTANT_ALPHA:
        return GL_CONSTANT_ALPHA;
    case BlendMode::ONE_MINUS_CONSTANT_ALPHA:
        return GL_ONE_MINUS_CONSTANT_ALPHA;
    }
}

auto Renderer::translateStencilOp(StencilOp operation) -> GLenum
{
    switch (operation)
    {
    case StencilOp::KEEP:
        return GL_KEEP;
    case StencilOp::ZERO:
        return GL_ZERO;
    case StencilOp::REPLACE:
        return GL_REPLACE;
    case StencilOp::INCR:
        return GL_INCR;
    case StencilOp::INCR_WRAP:
        return GL_INCR_WRAP;
    case StencilOp::DECR:
        return GL_DECR;
    case StencilOp::DECR_WRAP:
        return GL_DECR_WRAP;
    case StencilOp::INVERT:
        return GL_INVERT;
    }
}

void Renderer::loadStencil(const Stencil& stencil)
{
    glStencilMask(stencil.writeMask);
    glStencilOp(translateStencilOp(stencil.stencilFail), 
                translateStencilOp(stencil.depthFail), 
                translateStencilOp(stencil.bothPass));
    glStencilFunc(translateFuncEnum(stencil.func), stencil.funcRef, stencil.funcMask);
}

void Renderer::loadCullFace(const CullFace& cullFace)
{
    auto order = cullFace.order;
    auto glOrder = -1;
    switch (order)
    {
    case CullFaceOrder::CCW:
        glOrder = GL_CCW;
        break;
    case CullFaceOrder::CW:
        glOrder = GL_CW;
        break;
    default:
        break;
    }

    auto mode = cullFace.mode;
    auto glMode = -1;
    switch (mode)
    {
    case CullFaceMode::BACK:
        glMode = GL_BACK;
        break;
    case CullFaceMode::FRONT:
        glMode = GL_FRONT;
        break;
    case CullFaceMode::BOTH:
        glMode = GL_FRONT_AND_BACK;
        break;
    }

    glCullFace(glMode);
    glFrontFace(glOrder);
}

void Renderer::onReleaseSampler(ResourceIdentifier * identifier)
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
