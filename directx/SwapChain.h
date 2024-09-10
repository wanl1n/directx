#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
	private:
		IDXGISwapChain* m_swap_chain;
		ID3D11RenderTargetView* m_rtv;

	public:
		SwapChain();
		~SwapChain();

		bool init(HWND hwnd, UINT width, UINT height);
		bool present(bool vsync);
		bool release();

	private:
		friend class DeviceContext;
};

