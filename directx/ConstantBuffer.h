#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class ConstantBuffer
{
	private:
		UINT m_size_vertex;
		UINT m_size_list;

		ID3D11Buffer* m_buffer;
		RenderSystem* system = nullptr;

	private:
		friend class DeviceContext;

	public:
		ConstantBuffer(RenderSystem* system);
		~ConstantBuffer();

		bool load(void* buffer, UINT size_buffer);
		void update(DeviceContext* context, void* buffer);
		bool release();
};

