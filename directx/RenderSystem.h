#pragma once
#include <d3d11.h>

#include "Prerequisites.h"

class RenderSystem
{
	private:
		ID3D11Device* d3dDevice;
		D3D_FEATURE_LEVEL featureLevel;

		ID3D11DeviceContext* immContext;
		IDXGIDevice* dxgiDevice;
		IDXGIAdapter* dxgiAdapter;
		IDXGIFactory* dxgiFactory;

		DeviceContext* immDeviceContext;

		ID3DBlob* blob = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;
		friend class ConstantBuffer;
		friend class IndexBuffer;
		friend class BlendState;
		friend class VertexShader;
		friend class PixelShader;

	public:
		RenderSystem();
		~RenderSystem();

		bool init();
		bool release();

	public:
		SwapChain* createSwapChain();
		DeviceContext* getImmediateDeviceContext();

		VertexBuffer* createVertexBuffer();
		ConstantBuffer* createConstantBuffer();
		IndexBuffer* createIndexBuffer();

		BlendState* createBlendState(bool blending);

		// Shaders
		VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
		PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

		bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

		void releaseCompiledShader();
};

