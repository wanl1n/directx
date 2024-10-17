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
		PixelShader(RenderSystem* system);
		~PixelShader();

		void release();

	private:
		bool init(const void* shader_byte_code, size_t byte_code_size);
};

