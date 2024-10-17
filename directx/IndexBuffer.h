#pragma once
#include <d3d11.h>
#include "string"
#include <vector>

#include "Prerequisites.h"

class IndexBuffer
{
	private:
		UINT m_size_list;
		ID3D11Buffer* m_buffer;
		RenderSystem* system = nullptr;

		friend class DeviceContext;

	public:
		IndexBuffer(void* list_indices, UINT size_list, RenderSystem* system);
		IndexBuffer(std::vector<unsigned int> indices, RenderSystem* system);
		~IndexBuffer();

		UINT getSizeIndexList();
};

