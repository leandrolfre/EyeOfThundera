//#include "Shader.h"
//#include <iostream>
//#include <fstream>
//#include <sstream>
////#include <glad\glad.h>
//
//Shader::Shader()
//{
//}
//
//void Shader::load(const std::string& vertexPath, const std::string& fragmentPath)
//{
//	
//}
//
//void Shader::loadGeometry(const std::string& geometryPath) 
//{
//	/*auto geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryPath);
//	glAttachShader(_id, geometryShader);
//	glLinkProgram(_id);
//	glDeleteShader(geometryShader);*/
//}
//
//unsigned int Shader::compileShader(unsigned int type, const std::string& path)
//{
//	/*unsigned int shader = glCreateShader(type);
//
//	const char* shaderCode;
//
//	std::ifstream shaderFile(path);
//	std::stringstream ss;
//
//	ss << shaderFile.rdbuf();
//	const std::string tmpStr = ss.str();
//	shaderCode = tmpStr.c_str();
//	shaderFile.close();
//
//	glShaderSource(shader, 1, &shaderCode, nullptr);
//	glCompileShader(shader);
//
//	checkError(shader);
//
//	return shader;*/
//    return 0;
//}
//
//void Shader::checkError(unsigned int shader) const 
//{
//	/*int  success;
//	char infoLog[512];
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}*/
//}
//
//void Shader::use() 
//{
//	//glUseProgram(_id);
//}
//
//void Shader::setBool(const std::string &name, bool value) const 
//{
//	//glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
//}
//
//void Shader::setInt(const std::string &name, int value) const 
//{
//	//glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
//}
//
//void Shader::setFloat(const std::string &name, float value) const 
//{
//	//glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
//}
//
//void Shader::setMat4(const std::string &name, unsigned int count, bool transpose, const float* value) const
//{
//	//glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), count, transpose, value);
//}
//
//void Shader::setVec3(const std::string & name, const float x, const float y, const float z) const
//{
//	//glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
//}
//
//void Shader::setVec3(const std::string & name, const glm::vec3 & vector) const
//{
//	setVec3(name, vector.x, vector.y, vector.z);
//}
//
//void Shader::setVec4(const std::string & name, const float x, const float y, const float z, const float w) const
//{
//	//glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
//}
