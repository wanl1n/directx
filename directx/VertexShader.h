#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexShader
{
	private:
		ID3D11VertexShader* m_vs;
		RenderSystem* system = nullptr;

		friend class RenderSystem;
		friend class DeviceContext;

	public:
		VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system);
		~VertexShader();
};

