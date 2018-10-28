#pragma once

#include<string>

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

using releaseFunction = void(*) (Bindable*);
using releasePassFunction = void(*)(int, Bindable*);

class Renderer {
	
public:
	Renderer(int width, int height);
	~Renderer() = default;
	void initSystem();

	void enableDepth();
	void disableDepth();
	void enableStencil();
	void disableStencil();
	void enableCullFace();
	void disableCullFace();
	void enableMultiSample();
	void disableMultiSample();
	void clearActiveBuffers();
	void setCamera(Camera* camera);
	Camera* getCamera();

	void drawScene(VisibleSet& visibleSet);
	void draw(Geometry* geometry);
	void applyEffect(ShaderEffect* effect, bool primaryEffect);

	void loadAllResources(Spatial* scene);
	void releaseAllResources(Spatial* scene);

	void loadResources(Geometry* geometry);
	void releaseResources(Geometry* geometry);
	void loadResources(ShaderEffect* shaderEffect);
	void releaseResources(ShaderEffect* shaderEffect);

	void loadVertexProgram(VertexProgram* vertexProgram);
	void releaseVertexProgram(Bindable* vertexProgram);
	void loadPixelProgram(PixelProgram* pixelProgram);
	void releasePixelProgram(Bindable* pixelProgram);
	void loadTexture(Texture* texture);
	void releaseTexture(Bindable* texture);
	void loadVertexBuffer(int pass, const Attributes& attr, VertexBuffer* vBuffer);
	void releaseVertexBuffer(int pass, Bindable* bindable);
	void loadIndexBuffer(IndexBuffer* indexBuffer);
	void releaseIndexBuffer(Bindable* bindable);

	void onLoadVertexProgram(ResourceIdentifier* identifier, VertexProgram* vertexProgram);
	void onReleaseVertexProgram(ResourceIdentifier* identifier);
	void onLoadPixelProgram(ResourceIdentifier* identifier, PixelProgram* pixelProgram);
	void onReleasePixelProgram(ResourceIdentifier* identifier);
	void onLoadTexture(ResourceIdentifier* identifier, Texture* texture);
	void onReleaseTexture(ResourceIdentifier* identifier);
	void onLoadVertexBuffer(ResourceIdentifier* identifier, const Attributes& attr, VertexBuffer* vertexBuffer);
	void onReleaseVertexBuffer(ResourceIdentifier* identifier);
	void onLoadIndexBuffer(ResourceIdentifier* identifier, IndexBuffer* vertexBuffer);
	void onReleaseIndexBuffer(ResourceIdentifier* identifier);

private:
	void enableBuffer(int buffer);
	void disableBuffer(int buffer);
	void drawElements();

	int _width;
	int _height;
	int _activeBuffers;
	Camera* _activeCamera;
};