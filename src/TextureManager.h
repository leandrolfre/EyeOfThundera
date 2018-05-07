#pragma once

#include <unordered_map>
#include <string>

class TextureManager 
{
public:
	static TextureManager getInstance();
	unsigned int loadTexture(const std::string& texturePath);
private:
	TextureManager() = default;
private:
	std::unordered_map<std::string, int> _textureCache;
};