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
		IndexBuffer(RenderSystem* system);
		~IndexBuffer();

		bool load(void* list_indices, UINT size_list);
		bool load(std::vector<unsigned int> indices);
		bool release();
		UINT getSizeIndexList();
};

