#include "DeviceContext.h"
#include "SwapChain.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "BlendState.h"

#include "VertexShader.h"
#include "PixelShader.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : devContext(device_context) {}
DeviceContext::~DeviceContext() {}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = { red, green, blue, alpha };

	this->devContext->ClearRenderTargetView(swap_chain->renderView, clearColor);
	this->devContext->ClearDepthStencilView(swap_chain->depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	this->devContext->OMSetRenderTargets(1, &swap_chain->renderView, swap_chain->depthView);
}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, Vector4 color)
{
	FLOAT clearColor[] = { color.x, color.y, color.z, color.a };

	this->devContext->ClearRenderTargetView(swap_chain->renderView, clearColor);

	this->devContext->OMSetRenderTargets(1, &swap_chain->renderView, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;
	this->devContext->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer,&stride, &offset);
	this->devContext->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::setIndexBuffer(IndexBuffer* indexBuffer)
{
	this->devContext->IASetIndexBuffer(indexBuffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devContext->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawLineList(UINT vertex_count, UINT start_vertex_index)
{
	devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	devContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	this->devContext->RSSetViewports(1, &vp);
}

void DeviceContext::setBlendState(BlendState* blender)
{
	this->devContext->OMSetBlendState(blender->bs, nullptr, 0xFFFFFFFFu);
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	this->devContext->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::setPixelShader(PixelShader* pixel_shader)
{
	this->devContext->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer)
{
	this->devContext->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer)
{
	this->devContext->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

bool DeviceContext::release()
{
	this->devContext->Release();
	delete this;
	return true;
}
