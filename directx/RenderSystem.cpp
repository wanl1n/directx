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
	return new SwapChain(hwnd, width, height, this);
}

DeviceContext* RenderSystem::getImmediateDeviceContext()
{
	return this->immDeviceContext;
}

VertexBuffer* RenderSystem::createVertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize)
{
	return new VertexBuffer(vertices, vertexSize, listSize, sbc, bsSize, this);
}

VertexBuffer* RenderSystem::createVertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize)
{
	return new VertexBuffer(vertices, vertexSize, sbc, bsSize, this);
}

ConstantBuffer* RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	return new ConstantBuffer(buffer, size_buffer, this);
}

IndexBuffer* RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	return new IndexBuffer(list_indices, size_list, this);
}

IndexBuffer* RenderSystem::createIndexBuffer(std::vector<unsigned int> indices)
{
	return new IndexBuffer(indices, this);
}

BlendState* RenderSystem::createBlendState(bool blending)
{
	BlendState* bs = new BlendState(this);

	if (!bs->init(blending)) {
		bs->release();
		return nullptr;
	}

	return bs;
}

VertexShader* RenderSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader(shader_byte_code, byte_code_size, this);
	return vs;
}

PixelShader* RenderSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader(shader_byte_code, byte_code_size, this);
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
