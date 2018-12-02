#pragma once

#include <string>
#include <functional>
#include <vector>

class Bindable;
class Camera;
class Geometry;
//class VisibleSet;
class Spatial;
class Texture;
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
	void releaseProgram(Bindable* program);
	void loadTexture(Texture* texture);
	void releaseTexture(Bindable* texture);
	void loadVertexBuffer(VertexBuffer* vBuffer);

	void onLoadProgram(Program* vertexProgram);
	void onReleaseProgram(ResourceIdentifier* identifier);
	void onLoadTexture(Texture* texture);
	void onReleaseTexture(ResourceIdentifier* identifier);
	void onLoadVertexBuffer(VertexBuffer* vertexBuffer);
	void onReleaseVertexBuffer();

	void enableProgram(Program* vProgram);
	void disableProgram(Program* vProgram);
	void enableTexture(Texture* texture);
	void disableTexture(Texture* texture);
	void enableVertexBuffer(VertexBuffer* vBuffer);
	void disableVertexBuffer();

private:
	void drawElements();
	void setWorldTransformation();
	void restoreWorldTransformation();


	int _width;
	int _height;
	Camera* _activeCamera;
};