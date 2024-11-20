#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"

#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "BlendState.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>
#include <exception>

RenderSystem::RenderSystem() 
{
	D3D_DRIVER_TYPE driver_types[] = { D3D_DRIVER_TYPE_HARDWARE,
									   D3D_DRIVER_TYPE_WARP,
									   D3D_DRIVER_TYPE_REFERENCE };
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0 };
	UINT nufeatureLevels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++) {
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL,
			feature_levels, nufeatureLevels, D3D11_SDK_VERSION,
			&d3dDevice, &featureLevel, &immContext);
		if (SUCCEEDED(res))
			break;
	}

	if (FAILED(res))
		throw std::exception("RenderSystem failed to create device.");

	this->immDeviceContext = std::make_shared<DeviceContext>(immContext, this);

	this->d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	this->dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	this->dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	this->initRasterizerState();
}

RenderSystem::~RenderSystem() 
{
	this->dxgiDevice->Release();
	this->dxgiAdapter->Release();
	this->dxgiFactory->Release();
	this->immContext->Release();
	this->d3dDevice->Release();
}

SwapChainPtr RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;

	try {
		sc = std::make_shared<SwapChain>(hwnd, width, height, this);
	}
	catch(...) {}
	return sc;
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return this->immDeviceContext;
}

ID3D11Device* RenderSystem::getDevice()
{
	return this->d3dDevice;
}

ID3D11DeviceContext* RenderSystem::getContext()
{
	return this->immContext;
}

VertexBufferPtr RenderSystem::createVertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize)
{
	VertexBufferPtr vb = nullptr;

	try {
		vb = std::make_shared<VertexBuffer>(vertices, vertexSize, listSize, sbc, bsSize, this);
	}
	catch (...) {}
	return vb;
}

VertexBufferPtr RenderSystem::createVertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize)
{
	VertexBufferPtr vb = nullptr;

	try {
		vb = std::make_shared<VertexBuffer>(vertices, vertexSize, sbc, bsSize, this);
	}
	catch (...) {}
	return vb;
}

VertexBufferPtr RenderSystem::createVertexBuffer(std::vector<VertexMesh> vertices, UINT vertexSize, void* sbc, UINT bsSize)
{
	VertexBufferPtr vb = nullptr;

	try {
		vb = std::make_shared<VertexBuffer>(vertices, sbc, bsSize, this);
	}
	catch (...) {}
	return vb;
}

ConstantBufferPtr RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBufferPtr cb = nullptr;

	try {
		cb = std::make_shared<ConstantBuffer>(buffer, size_buffer, this);
	}
	catch (...) {}
	return cb;
}

IndexBufferPtr RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	IndexBufferPtr ib = nullptr;

	try {
		ib = std::make_shared<IndexBuffer>(list_indices, size_list, this);
	}
	catch (...) {}
	return ib;
}

IndexBufferPtr RenderSystem::createIndexBuffer(std::vector<unsigned int> indices)
{
	IndexBufferPtr ib = nullptr;

	try {
		ib = std::make_shared<IndexBuffer>(indices, this);
	}
	catch (...) {}
	return ib;
}

BlendStatePtr RenderSystem::createBlendState(bool blending)
{
	BlendStatePtr bs = nullptr;

	try {
		bs = std::make_shared<BlendState>(blending, this);
	}
	catch (...) {}
	return bs;
}

VertexShaderPtr RenderSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShaderPtr vs = nullptr;
	try {
		vs = std::make_shared<VertexShader>(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return vs;
}

PixelShaderPtr RenderSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShaderPtr ps = nullptr;
	try {
		ps = std::make_shared<PixelShader>(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return ps;
}

bool RenderSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &this->blob, &error_blob))) {
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = blob->GetBufferPointer();
	*byte_code_size = blob->GetBufferSize();

	return true;
}

bool RenderSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &this->blob, &error_blob))) {
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = blob->GetBufferPointer();
	*byte_code_size = blob->GetBufferSize();

	return true;
}

void RenderSystem::releaseCompiledShader()
{
	if (blob) blob->Release();
}

void RenderSystem::setRasterizerState(bool cullFront)
{
	if (cullFront)
		this->immContext->RSSetState(cullFrontState);
	else
		this->immContext->RSSetState(cullBackState);
}

void RenderSystem::initRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;
	d3dDevice->CreateRasterizerState(&desc, &cullFrontState);

	desc.CullMode = D3D11_CULL_BACK;
	d3dDevice->CreateRasterizerState(&desc, &cullBackState);
}
