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
		SwapChain(RenderSystem* system);
		~SwapChain();

		bool init(HWND hwnd, UINT width, UINT height);

		bool present(bool vsync);
		bool release();

	private:
		friend class DeviceContext;
};

