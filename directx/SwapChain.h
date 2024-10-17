#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class SwapChain
{
	private:
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderView;
		ID3D11DepthStencilView* depthView;
		RenderSystem* system = nullptr;

	public:
		SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);
		~SwapChain();

		bool present(bool vsync);

	private:
		friend class DeviceContext;
};

