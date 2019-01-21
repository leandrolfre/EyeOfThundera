#pragma once

#include <glad\glad.h>
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
class RenderState;
struct Depth;
struct Stencil;
struct CullFace;
enum class FilterMode;
enum class WrapMode;
enum class ShaderType;
enum class BlendMode;
enum class Func;

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

	void loadSampler(Sampler2D* texture);
	void onLoadSampler(Sampler2D* sampler);
	void enableSampler(Sampler2D* texture);
	void disableSampler(Sampler2D* texture);
	void onReleaseSampler(ResourceIdentifier* identifier);

	void loadSampler(SamplerCube* sampler);
	void releaseSampler(Bindable* sampler);
	void onLoadSampler(SamplerCube* sampler);
	void enableSampler(SamplerCube* sampler);
	void disableSampler(SamplerCube* sampler);

    void loadRenderState(RenderState* renderState);
    auto translateFuncEnum(Func func) -> GLenum;
    auto translateBlendMode(BlendMode mode) -> GLenum;
    auto translateStencilOp(StencilOp operation)->GLenum;
    void loadStencil(const Stencil& stencil);
    void loadCullFace(const CullFace& cullFace);

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
    int _currentBufferMask;
	Camera* _activeCamera;
};