#pragma once

#include "Bindable.h"
#include <string>
#include <vector>

//Texture Wrapping (s, t, r): Repeat, MirroredRepeat, ClampToEdge, ClampToBorder
//Texture Filtering (Minifying, Magnifying): Nearest, Linear
//Texture Mipmap(Minifying): NearestNearest, LinearNearest, NearestLinear, LinearLinear
//Generate Mipmap?

struct Texture;

enum class WrapMode 
{
	Repeat,
	MirroredRepeat,
	ClampToEdge,
	ClamptoBorder
};

enum class FilterMode
{
	Nearest,
	Linear,
	NearestNearest,
	LinearNearest,
	NearestLinear,
	LinearLinear
};

class Sampler : public Bindable 
{
public:
	std::string _name;
	std::string _path;
	unsigned int unitID;
	FilterMode minFilter;
	FilterMode magFilter;
	WrapMode wrapS;
	WrapMode wrapT;
	WrapMode wrapR;
	bool generateMipmap;
	virtual void init() = 0;
protected:
	Sampler();
	Sampler(const std::string& name, const std::string& path);
	virtual ~Sampler();
};

class Sampler2D : public Sampler
{
public:
	Sampler2D(const std::string& name, const std::string& path);
	virtual ~Sampler2D();
	void init();
	Texture* _texture;
};

class SamplerCube : public Sampler
{
public:
	SamplerCube(const std::string& name, const std::string& path, const std::string& ext);
	virtual ~SamplerCube();
	void init();
	const unsigned char _maxTextures = 6;
	std::string _ext;
	std::vector<Texture*> _textures;
};