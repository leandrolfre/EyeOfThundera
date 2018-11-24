#pragma once

class RenderState
{
public:
	RenderState() = default;
	~RenderState() = default;
	void init();
	void enableDepth();
	void disableDepth();
	void enableStencil();
	void disableStencil();
	void enableCullFace();
	void disableCullFace();
	void enableMultiSample();
	void disableMultiSample();
	void clearActiveBuffers();

private:
	void enableBuffer(int buffer);
	void disableBuffer(int buffer);
	int _activeBuffers;
};