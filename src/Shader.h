//#pragma once
//
//#include <string>
//#include <glm/glm.hpp>
//#include "Bindable.h"
//
//class Shader : public Bindable
//{
//public:
//	Shader();
//    ~Shader();
//	void load(const std::string & vertexPath, const std::string & fragmentPath);
//	void loadGeometry(const std::string& geometryPath);
//	void use();
//	void setBool(const std::string& name, bool value) const;
//	void setInt(const std::string& name, int value) const;
//	void setFloat(const std::string& name, float value) const;
//	void setMat4(const std::string& name, unsigned int count, bool transpose, const float* value) const;
//	void setVec3(const std::string& name, const float x, const float y, const float z) const;
//	void setVec3(const std::string& name, const glm::vec3& vector) const;
//	void setVec4(const std::string& name, const float x, const float y, const float z, const float w) const;
//
//private:
//	unsigned int compileShader(unsigned int type, const std::string & path);
//	void checkError(unsigned int shader) const;
//
//private:
//	unsigned int _id;
//};