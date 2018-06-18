#define STB_IMAGE_IMPLEMENTATION
#include "TextureManager.h"
#include "stb_image.h"
#include <glad\glad.h>

TextureManager& TextureManager::getInstance() 
{
	static TextureManager _instance;
	return _instance;
}

unsigned int TextureManager::loadTexture(const std::string& texturepath)
{
	auto textureIt = _textureCache.find(texturepath);
	if (textureIt != _textureCache.end())
	{
		return textureIt->second;
	}

	int width, height, channels;
	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(texturepath.c_str(), &width, &height, &channels, 4);
	GLuint textureId = 0;
	if (data)
	{
		glGenTextures(1, &textureId);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		_textureCache.insert({ texturepath , textureId });
	}

	return textureId;
}

unsigned int TextureManager::loadCubeMapTexture(const std::string& dirPath, const std::string& imageExt)
{
	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	int width, height, channels;
	for (int i = 0; i < 6; ++i) 
	{
		auto path = dirPath + std::to_string(i) + "." + imageExt;
		stbi_set_flip_vertically_on_load(false);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	return textureId;
}