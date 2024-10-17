#pragma once
#include <d3d11.h>
#include <vector>
#include "string"

#include "Vector3.h"
#include "Vertex.h"

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
		VertexBuffer(RenderSystem* system);
		~VertexBuffer();

		bool loadQuad(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
		bool loadCircle(std::vector<CircleVertex> list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
		bool loadIndexed(std::vector<Vertex3D> vertices, UINT size_vertex, void* shader_byte_code, UINT size_byte_shader);
		bool loadTool(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
		bool release();

	public:
		UINT getSizeVertexList();
};

