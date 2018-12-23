#pragma once

#include <string>
#include <functional>
#include <vector>

class Bindable;
class Camera;
class Geometry;
//class VisibleSet;
class Spatial;
class Sampler2D;
class SamplerCube;
class VertexBuffer;
class ResourceIdentifier;
class Program;
class Material;

using LoadProc = void*(*)(const char *name);

class Renderer {
	
public:
	Renderer(int width, int height);
	~Renderer();
	bool initSystem(LoadProc proc) const;

	void setCamera(Camera* camera);
	Camera* getCamera();
	void drawScene(std::vector<std::unique_ptr<Geometry>>& visibleSet);
	//void drawScene(VisibleSet& visibleSet);
	void draw(Geometry* geometry);
	void applyMaterial(Material* mat);

	void loadAllResources(Spatial* scene);
	void releaseAllResources(Spatial* scene);

	void loadResources(Geometry* geometry);
	void releaseResources(Geometry* geometry);
	void loadResources(Material* mat);
	void releaseResources(Material* mat);

	void loadProgram(Program* vertexProgram);
	void onLoadProgram(Program* vertexProgram);
	void releaseProgram(Bindable* program);
	void onReleaseProgram(ResourceIdentifier* identifier);
	void enableProgram(Program* vProgram);
	void disableProgram(Program* vProgram);

	void loadVertexBuffer(VertexBuffer* vBuffer);
	void onLoadVertexBuffer(VertexBuffer* vertexBuffer);
	void onReleaseVertexBuffer();
	void enableVertexBuffer(VertexBuffer* vBuffer);
	void disableVertexBuffer();

	void loadSampler2D(Sampler2D* texture);
	void releaseSampler2D(Bindable* texture);
	void onLoadSampler2D(Sampler2D* sampler);
	void enableSampler2D(Sampler2D* texture);
	void disableSampler2D(Sampler2D* texture);
	void onReleaseSampler2D(ResourceIdentifier* identifier);

	void loadSamplerCube(SamplerCube* sampler);
	void releaseSamplerCube(Bindable* sampler);
	void onLoadSamplerCube(SamplerCube* sampler);
	void enableSamplerCube(SamplerCube* sampler);
	void disableSamplerCube(SamplerCube* sampler);
	void onReleaseSamplerCube(ResourceIdentifier* identifier);

	GLint translateFilterMode(FilterMode mode);
	GLint translateWrapMode(WrapMode mode);


private:
	void drawElements();
	void setWorldTransformation();
	void restoreWorldTransformation();
	unsigned int compileShader(ShaderType type, Program* program);
	void checkError(unsigned int shader) const;


	int _width;
	int _height;
	Camera* _activeCamera;
};