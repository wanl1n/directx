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
	BlendState(bool blending, RenderSystem* system);
	~BlendState();
};