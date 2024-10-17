#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class BlendState
{
private:
	ID3D11BlendState* bs;
	RenderSystem* system = nullptr;

	friend class RenderSystem;
	friend class DeviceContext;

public:
	BlendState(RenderSystem* system);
	~BlendState();

	void release();

private:
	bool init(bool blending);
};

