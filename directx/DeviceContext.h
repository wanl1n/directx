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
		
		void clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);
		void clearRenderTargetColor(const SwapChainPtr& swap_chain, Vector4 color);
		void setVertexBuffer(const VertexBufferPtr& vertex_buffer);
		void setIndexBuffer(const IndexBufferPtr& indexBuffer);
		void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
		void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
		void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
		void drawLineList(UINT vertex_count, UINT start_vertex_index);
		void setViewportSize(UINT width, UINT height);

		void setRenderConfig(VertexShader* vs, PixelShader* ps);
		void setBlendState(const BlendStatePtr& blender);
		void setVertexShader(const VertexShaderPtr& vertex_shader);
		void setPixelShader(const PixelShaderPtr& pixel_shader);

		void setTexture(const TexturePtr& texture);

		void setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);
		void setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);
};

