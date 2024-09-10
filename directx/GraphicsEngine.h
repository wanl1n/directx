#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
	private:
		ID3D11Device* m_d3d_device;
		D3D_FEATURE_LEVEL m_feature_level;
		ID3D11DeviceContext* m_imm_context;

		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;

		DeviceContext* m_imm_device_context;

	private:
		friend class SwapChain;

	public:
		GraphicsEngine();
		~GraphicsEngine();

		bool init();
		bool release();

	public:
		SwapChain* createSwapChain();
		DeviceContext* getImmediateDeviceContext();

	public:
		static GraphicsEngine* get();
};

