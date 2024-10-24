#include "ConstantBuffer.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include <exception>

ConstantBuffer::ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system) : 
	system(system), m_buffer(0) 
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(system->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		throw std::exception("Constant Buffer creation failed.");
}

ConstantBuffer::~ConstantBuffer() 
{
	if (this->m_buffer) this->m_buffer->Release();
}

void ConstantBuffer::update(DeviceContextPtr context, void* buffer)
{
	context->devContext->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}