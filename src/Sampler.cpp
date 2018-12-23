#include "Sampler.h"
#include "TextureManager.h"

Sampler::Sampler()
{
}

Sampler::Sampler(const std::string& name, const std::string & path) : _path(path), _name(name), generateMipmap(true)
{
}

Sampler::~Sampler()
{
}

Sampler2D::Sampler2D(const std::string& name, const std::string& path) : Sampler(name, path)
{
}

Sampler2D::~Sampler2D()
{
}

void Sampler2D::init() 
{
	_texture = TextureManager::getInstance().loadTexture(_path);
	wrapS = wrapT = WrapMode::Repeat;
	minFilter = FilterMode::NearestNearest;
	magFilter = FilterMode::Linear;
}

SamplerCube::SamplerCube(const std::string& name, const std::string& path, const std::string& ext) : Sampler(name, path), _ext(ext)
{
}

SamplerCube::~SamplerCube()
{
}

void SamplerCube::init() 
{
	_textures.reserve(_maxTextures);
	for (int i = 0; i < _maxTextures; ++i) 
	{
		auto path = _path + std::to_string(i) + "." + _ext;
		auto texture = TextureManager::getInstance().loadTexture(_path);
		_textures.push_back(texture);
	}
	wrapS = wrapT = wrapR = WrapMode::ClampToEdge;
	minFilter = magFilter = FilterMode::Linear;
}
