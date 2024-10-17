#pragma once
#include <d3d11.h>
#include "Math.h"

#include "Prerequisites.h"

class DeviceContext
{
	private:
		ID3D11DeviceContext* devContext;
		RenderSystem* system = nullptr;

	private:
		friend class ConstantBuffer;

	public:
		DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
		~DeviceContext();
		
		void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
		void clearRenderTargetColor(SwapChain* swap_chain, Vector4 color);
		void setVertexBuffer(VertexBuffer* vertex_buffer);
		void setIndexBuffer(IndexBuffer* indexBuffer);
		void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
		void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
		void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
		void drawLineList(UINT vertex_count, UINT start_vertex_index);
		void setViewportSize(UINT width, UINT height);

		void setBlendState(BlendState* blender);

		void setVertexShader(VertexShader* vertex_shader);
		void setPixelShader(PixelShader* pixel_shader);

		void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
		void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);
};

