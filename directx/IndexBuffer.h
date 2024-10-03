#pragma once
#include <d3d11.h>
#include "string"

class DeviceContext;

class IndexBuffer
{
	private:
		UINT m_size_list;
		ID3D11Buffer* m_buffer;

		friend class DeviceContext;

	public:
		IndexBuffer();
		~IndexBuffer();

		bool load(void* list_indices, UINT size_list);
		bool release();
		UINT getSizeIndexList();
};

