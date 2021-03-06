#define STB_IMAGE_IMPLEMENTATION
#include "TextureManager.h"
#include "stb_image.h"
#include <glad\glad.h>

TextureManager TextureManager::getInstance() 
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
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturepath.c_str(), &width, &height, &channels, 0);
	GLuint textureId = 0;
	if (data)
	{
		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		glGenTextures(1, &textureId);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		_textureCache.insert({ texturepath , textureId });
	}

	return textureId;
}