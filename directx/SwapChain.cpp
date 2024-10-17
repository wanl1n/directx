#include "SwapChain.h"
#include "RenderSystem.h"
#include <exception>

SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system) : system(system) 
{
	// Create Swap Chain.
	ID3D11Device* device = system->d3dDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = system->dxgiFactory->CreateSwapChain(device, &desc, &this->swapChain);
	if (FAILED(hr)) throw std::exception("SwapChain creation failed.");

	ID3D11Texture2D* buffer = NULL;
	hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(hr)) throw std::exception("Buffer creation failed.");

	// Create Render Target View.
	hr = device->CreateRenderTargetView(buffer, NULL, &this->renderView);
	buffer->Release();
	if (FAILED(hr))	throw std::exception("RenderTargetView creation failed.");

	// Create Depth Stencil.
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;

	HRESULT depthResult = device->CreateTexture2D(&texDesc, NULL, &buffer);
	if (FAILED(depthResult)) throw std::exception("Texture2D creation failed.");

	HRESULT depthStencilResult = device->CreateDepthStencilView(buffer, NULL, &this->depthView);
	if (FAILED(depthStencilResult)) throw std::exception("DepthStencilView creation failed.");

	buffer->Release();
}

SwapChain::~SwapChain() 
{
	this->swapChain->Release();
	this->renderView->Release();
	this->depthView->Release();
}

bool SwapChain::present(bool vsync)
{
	swapChain->Present(vsync, NULL);

	return true;
}