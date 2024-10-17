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

RenderSystem::RenderSystem() {}
RenderSystem::~RenderSystem() {}

bool RenderSystem::init()
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
		return false;

	this->immDeviceContext = new DeviceContext(immContext, this);

	this->d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	this->dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	this->dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	return true;
}

bool RenderSystem::release()
{
	this->dxgiDevice->Release();
	this->dxgiAdapter->Release();
	this->dxgiFactory->Release();
	this->immContext->Release();
	this->d3dDevice->Release();

	delete this->immDeviceContext;

	return true;
}

SwapChain* RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChain* sc = nullptr;

	try {
		sc = new SwapChain(hwnd, width, height, this);
	}
	catch(...) {}
	return sc;
}

DeviceContext* RenderSystem::getImmediateDeviceContext()
{
	return this->immDeviceContext;
}

VertexBuffer* RenderSystem::createVertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize)
{
	VertexBuffer* vb = nullptr;

	try {
		vb = new VertexBuffer(vertices, vertexSize, listSize, sbc, bsSize, this);
	}
	catch (...) {}
	return vb;
}

VertexBuffer* RenderSystem::createVertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize)
{
	VertexBuffer* vb = nullptr;

	try {
		vb = new VertexBuffer(vertices, vertexSize, sbc, bsSize, this);
	}
	catch (...) {}
	return vb;
}

ConstantBuffer* RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBuffer* cb = nullptr;

	try {
		cb = new ConstantBuffer(buffer, size_buffer, this);
	}
	catch (...) {}
	return cb;
}

IndexBuffer* RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	IndexBuffer* ib = nullptr;

	try {
		ib = new IndexBuffer(list_indices, size_list, this);
	}
	catch (...) {}
	return ib;
}

IndexBuffer* RenderSystem::createIndexBuffer(std::vector<unsigned int> indices)
{
	IndexBuffer* ib = nullptr;

	try {
		ib = new IndexBuffer(indices, this);
	}
	catch (...) {}
	return ib;
}

BlendState* RenderSystem::createBlendState(bool blending)
{
	BlendState* bs = nullptr;

	try {
		bs = new BlendState(blending, this);
	}
	catch (...) {}
	return bs;
}

VertexShader* RenderSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = nullptr;
	try {
		vs = new VertexShader(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return vs;
}

PixelShader* RenderSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = nullptr;
	try {
		ps = new PixelShader(shader_byte_code, byte_code_size, this);
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
