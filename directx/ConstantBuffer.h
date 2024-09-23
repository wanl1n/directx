#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer
{
	private:
		UINT m_size_vertex;
		UINT m_size_list;

		ID3D11Buffer* m_buffer;

	private:
		friend class DeviceContext;

	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool load(void* buffer, UINT size_buffer);
		void update(DeviceContext* context, void* buffer);
		bool release();
};

