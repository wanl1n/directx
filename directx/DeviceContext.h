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
		
		void clearRenderTargetColor(SwapChainPtr swap_chain, float red, float green, float blue, float alpha);
		void clearRenderTargetColor(SwapChainPtr swap_chain, Vector4 color);
		void setVertexBuffer(VertexBufferPtr vertex_buffer);
		void setIndexBuffer(IndexBufferPtr indexBuffer);
		void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
		void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
		void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
		void drawLineList(UINT vertex_count, UINT start_vertex_index);
		void setViewportSize(UINT width, UINT height);

		void setBlendState(BlendStatePtr blender);

		void setVertexShader(VertexShaderPtr vertex_shader);
		void setPixelShader(PixelShaderPtr pixel_shader);

		void setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr buffer);
		void setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr buffer);
};

