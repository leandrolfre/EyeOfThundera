#pragma once

#include <memory>
#include <unordered_map>
#include <string>

struct Texture
{
	std::string path;
	int width;
	int height;
	int channels;
	unsigned char* data;
};

using TextureUPtr = std::unique_ptr<Texture>;

class TextureManager 
{
public:
	static TextureManager& getInstance();
	Texture* loadTexture(const std::string& texturePath);
private:
	TextureManager() = default;
private:
	std::unordered_map<std::string, TextureUPtr> _textureCache;
};