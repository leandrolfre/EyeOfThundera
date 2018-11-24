#pragma once

#include <string>
#include <functional>

class Camera;
class VisibleSet;
class Geometry;
class ShaderEffect;
class Bindable;
class Spatial;
class VertexProgram;
class PixelProgram;
class Texture;
class Attributes;
class VertexBuffer;
class IndexBuffer;
class ResourceIdentifier;
class Program;

class Renderer {
	
public:
	Renderer(int width, int height);
	~Renderer() = default;
	void initSystem();

	void setCamera(Camera* camera);
	Camera* getCamera();

	void drawScene(VisibleSet& visibleSet);
	void draw(Geometry* geometry);
	void applyEffect(ShaderEffect* effect, bool& primaryEffect);

	void loadAllResources(Spatial* scene);
	void releaseAllResources(Spatial* scene);

	void loadResources(Geometry* geometry);
	void releaseResources(Geometry* geometry);
	void loadResources(ShaderEffect* shaderEffect);
	void releaseResources(ShaderEffect* shaderEffect);

	void loadProgram(Program* vertexProgram);
	void releaseProgram(Bindable* program);
	void loadTexture(Texture* texture);
	void releaseTexture(Bindable* texture);
	void loadVertexBuffer(VertexBuffer* vBuffer);
	void releaseVertexBuffer(Bindable* bindable);

	void onLoadProgram(ResourceIdentifier* identifier, Program* vertexProgram);
	void onReleaseProgram(ResourceIdentifier* identifier);
	void onLoadTexture(ResourceIdentifier* identifier, Texture* texture);
	void onReleaseTexture(ResourceIdentifier* identifier);
	void onLoadVertexBuffer(ResourceIdentifier* identifier, VertexBuffer* vertexBuffer);
	void onReleaseVertexBuffer(ResourceIdentifier* identifier);

	void enableProgram(Program* vProgram);
	void disableProgram(Program* vProgram);
	void enableTexture(Texture* texture);
	void disableTexture(Texture* texture);
	ResourceIdentifier* enableVertexBuffer(VertexBuffer* vBuffer);
	void disableVertexBuffer(ResourceIdentifier* ri);

private:
	void drawElements();
	void setWorldTransformation();
	void restoreWorldTransformation();


	int _width;
	int _height;
	Camera* _activeCamera;
	Geometry* _currentGeometry;

};