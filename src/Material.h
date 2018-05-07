#pragma once

#include <glm/glm.hpp>
#include <string>

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
} ;

class Material 
{
public:
	Material() = default;
public:
	float shininess;
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	Texture diffuseMap;
	Texture specularMap;
};