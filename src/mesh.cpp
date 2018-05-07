#include "mesh.h"
#include "shader.hpp"
#include <glad\glad.h>
#include "Material.h"


void Mesh::draw(const Shader& shader)
{
	unsigned int textureIdx = 0;
	shader.setFloat("material.shininess", _material->shininess);
	shader.setVec3("material.ka", _material->ka);
	shader.setVec3("material.kd", _material->kd);
	shader.setVec3("material.ks", _material->ks);
		
	shader.setInt("material.diffuse", textureIdx);
	glActiveTexture(GL_TEXTURE0 + textureIdx);
	glBindTexture(GL_TEXTURE_2D, _material->diffuseMap.id);

	shader.setInt("material.specular", ++textureIdx);
	glActiveTexture(GL_TEXTURE0 + textureIdx);
	glBindTexture(GL_TEXTURE_2D, _material->specularMap.id);

	// draw mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setVertices(std::vector<Vertex> v)
{
	_vertices = v;
}

void Mesh::setIndices(std::vector<unsigned int> i)
{
	_indices = i;
}

void Mesh::setMaterial(std::unique_ptr<Material> m)
{
	_material = move(m);
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
