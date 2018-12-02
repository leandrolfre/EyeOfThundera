//#include "mesh.h"
//#include "Shader.h"
//#include <glad\glad.h>
//#include "Material.h"


//void Mesh::draw(const Shader& shader)
//{
//	unsigned int textureIdx = 0;
//	shader.setFloat("material.shininess", _material->shininess);
//	shader.setVec3("material.ka", _material->ka);
//	shader.setVec3("material.kd", _material->kd);
//	shader.setVec3("material.ks", _material->ks);
//		
//	shader.setInt("material.diffuse", textureIdx);
//	glActiveTexture(GL_TEXTURE0 + textureIdx);
//	glBindTexture(GL_TEXTURE_2D, _material->diffuseMap.id);
//
//	shader.setInt("material.specular", ++textureIdx);
//	glActiveTexture(GL_TEXTURE0 + textureIdx);
//	glBindTexture(GL_TEXTURE_2D, _material->specularMap.id);
//
//	// draw mesh
//	glBindVertexArray(_vao);
//	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
//	
//	glBindVertexArray(0);
//	glActiveTexture(GL_TEXTURE0);
//}
//
