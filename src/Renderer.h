#pragma once

#include<string>

class Camera;

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
private:
	void enableBuffer(int buffer);
	void disableBuffer(int buffer);
private:
	int _width;
	int _height;
	int _activeBuffers;
	Camera* _activeCamera;
};