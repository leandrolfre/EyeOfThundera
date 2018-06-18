#pragma once

#include <unordered_map>
#include <string>

class TextureManager 
{
public:
	static TextureManager& getInstance();
	unsigned int loadTexture(const std::string& texturePath);
	unsigned int loadCubeMapTexture(const std::string& dirPath, const std::string& imageExt);
private:
	TextureManager() = default;
private:
	std::unordered_map<std::string, int> _textureCache;
};