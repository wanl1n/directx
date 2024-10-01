#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;
GraphicsEngine* GraphicsEngine::get() {
	/*if (sharedInstance == nullptr)
		sharedInstance = new GraphicsEngine();*/

	return sharedInstance;
}

GraphicsEngine::GraphicsEngine() {}

GraphicsEngine::~GraphicsEngine() {}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	delete sharedInstance;
	if (sharedInstance != NULL)
		sharedInstance->release();
}

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

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

void GraphicsEngine::createBlendState(bool blending)
{
	D3D11_BLEND_DESC desc = {};

	if (blending) {
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	else {
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	// Color Blend State
	ID3D11BlendState* blender = NULL;
	this->m_d3d_device->CreateBlendState(&desc, &blender);

	// Bind Color State
	this->m_imm_context->OMSetBlendState(blender, nullptr, 0xFFFFFFFFu);
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size)) {
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size)) {
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &this->m_blob, &error_blob))) {
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &this->m_blob, &error_blob))) {
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (m_blob) m_blob->Release();
}
