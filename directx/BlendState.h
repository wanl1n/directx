#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class BlendState
{
private:
	ID3D11BlendState* bs;

	friend class GraphicsEngine;
	friend class DeviceContext;

public:
	BlendState();
	~BlendState();

	void release();

private:
	bool init(bool blending);
};

