#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context)
{
	this->m_device_context = device_context;
}

DeviceContext::~DeviceContext()
{
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha };
	this->m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);

	return true;
}

bool DeviceContext::release()
{
	this->m_device_context->Release();
	delete this;
	return true;
}
