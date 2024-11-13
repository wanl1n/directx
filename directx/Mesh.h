#pragma once
#include <d3d11.h>
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class DeviceContext;

class Mesh : public Resource
{
	private:
		VertexBufferPtr vb;
		IndexBufferPtr ib;

		friend class DeviceContext;

	public:
		Mesh(const wchar_t* path);
		~Mesh();

	public:
		const VertexBufferPtr& getVertexBuffer();
		const IndexBufferPtr& getIndexBuffer();
};

