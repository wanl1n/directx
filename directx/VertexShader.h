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
		VertexShader(RenderSystem* system);
		~VertexShader();

		void release();

	private:
		bool init(const void* shader_byte_code, size_t byte_code_size);
};

