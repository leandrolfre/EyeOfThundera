#define STB_IMAGE_IMPLEMENTATION
#include "TextureManager.h"
#include "stb_image.h"
#include <glad\glad.h>

TextureManager& TextureManager::getInstance() 
{
	static TextureManager _instance;
	return _instance;
}

Texture* TextureManager::loadTexture(const std::string& texturepath)
{
	auto textureIt = _textureCache.find(texturepath);
	if (textureIt != _textureCache.end())
	{
		return textureIt->second.get();
	}
	auto texture = new Texture();
	stbi_set_flip_vertically_on_load(false);
	texture->data = stbi_load(texturepath.c_str(), &texture->width, &texture->height, &texture->channels, 4);
	if (texture->data)
	{
		_textureCache.insert({ texturepath , std::unique_ptr<Texture>(texture) });
	}

	return texture;
}

//unsigned int TextureManager::loadCubeMapTexture(const std::string& dirPath, const std::string& imageExt)
//{
//	GLuint textureId = 0;
//	glGenTextures(1, &textureId);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
//	int width, height, channels;
//	for (int i = 0; i < 6; ++i) 
//	{
//		auto path = dirPath + std::to_string(i) + "." + imageExt;
//		stbi_set_flip_vertically_on_load(false);
//		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		stbi_image_free(data);
//	}
//
//	return textureId;
//}