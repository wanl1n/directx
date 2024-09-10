#pragma once
#include <d3d11.h>

class SwapChain
{
	private:
		IDXGISwapChain* m_swap_chain;

	public:
		SwapChain();
		~SwapChain();

		bool init(HWND hwnd, UINT width, UINT height);
		bool release();
};

