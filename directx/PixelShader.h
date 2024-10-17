#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class PixelShader
{
	private:
		ID3D11PixelShader* m_ps;
		RenderSystem* system = nullptr;

		friend class RenderSystem;
		friend class DeviceContext;

	public:
		PixelShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system);
		~PixelShader();
};

