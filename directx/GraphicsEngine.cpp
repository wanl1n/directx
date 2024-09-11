#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine() {}

GraphicsEngine::~GraphicsEngine() {}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] = { D3D_DRIVER_TYPE_HARDWARE,
									   D3D_DRIVER_TYPE_WARP,
									   D3D_DRIVER_TYPE_REFERENCE };
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0 };
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++) {
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, 
								feature_levels, num_feature_levels, D3D11_SDK_VERSION, 
								&m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
	}
	
	if (FAILED(res))
		return false;

	this->m_imm_device_context = new DeviceContext(m_imm_context);

	this->m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	this->m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	this->m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	this->m_dxgi_device->Release();
	this->m_dxgi_adapter->Release();
	this->m_dxgi_factory->Release();
	this->m_imm_context->Release();
	this->m_d3d_device->Release();

	this->m_imm_device_context->release();

	return true;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

bool GraphicsEngine::createShaders() {
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
	return true;

}

bool GraphicsEngine::setShaders() {
	m_imm_context->VSSetShader(m_vs, nullptr, 0);
	m_imm_context->PSSetShader(m_ps, nullptr, 0);
	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size) {
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();

}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}
