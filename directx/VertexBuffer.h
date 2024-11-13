#pragma once
#include <d3d11.h>
#include <vector>
#include "string"

#include "Vector3.h"
#include "Vertex.h"
#include "VertexMesh.h"

#include "Prerequisites.h"

class VertexBuffer
{
	private:
		UINT m_size_vertex;
		UINT m_size_list;

		ID3D11Buffer* m_buffer;
		ID3D11InputLayout* m_layout;
		RenderSystem* system = nullptr;

	private:
		friend class DeviceContext;

	public:
		VertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize, RenderSystem* system);
		VertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize, RenderSystem* system);
		VertexBuffer(std::vector<VertexMesh> vertices, void* sbc, UINT bsSize, RenderSystem* system);
		~VertexBuffer();

	public:
		UINT getSizeVertexList();
};

