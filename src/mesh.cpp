#include "mesh.h"
#include "shader.hpp"
#include <glad\glad.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	_vertices = vertices;
	_indices = indices;
	_textures = textures;

	init();
}

void Mesh::draw(Shader shader)
{
	unsigned int diffuseIdx = 0;
	unsigned int specularIdx = 0;

	for (int i = 0; i < _textures.size(); i++) 
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = _textures[i].type;
		
		if (name == "texture_diffuse") 
		{
			number = std::to_string(diffuseIdx++);
			name = "diffuse";
		}
		else if (name == "texture_specular") 
		{
			number = std::to_string(specularIdx++);
			name = "specular";
			shader.setFloat("material.shininess", _textures[i].shininess);
		}
			
		shader.setVec3("material.ka", _textures[i].ka);
		shader.setVec3("material.kd", _textures[i].kd);
		shader.setVec3("material.ks", _textures[i].ks);
		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, _textures[i].id);
	}
	// draw mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::init()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	//vertex normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindVertexArray(0);
}
