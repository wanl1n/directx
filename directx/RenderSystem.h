#pragma once
#include <d3d11.h>
#include <vector>
#include "Vertex.h"
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

		DeviceContextPtr immDeviceContext;

		ID3DBlob* blob = nullptr;

		ID3D11RasterizerState* cullFrontState = nullptr;
		ID3D11RasterizerState* cullBackState = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;
		friend class ConstantBuffer;
		friend class IndexBuffer;
		friend class BlendState;
		friend class VertexShader;
		friend class PixelShader;
		friend class Texture;

	public:
		RenderSystem();
		~RenderSystem();

	public:
		SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
		DeviceContextPtr getImmediateDeviceContext();
		ID3D11Device* getDevice();
		ID3D11DeviceContext* getContext();

		VertexBufferPtr createVertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize);
		VertexBufferPtr createVertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize);
		VertexBufferPtr createVertexBuffer(std::vector<VertexMesh> vertices, UINT vertexSize, void* sbc, UINT bsSize);
		ConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
		IndexBufferPtr createIndexBuffer(void* list_indices, UINT size_list);
		IndexBufferPtr createIndexBuffer(std::vector<unsigned int> indices);

		BlendStatePtr createBlendState(bool blending);

		// Shaders
		VertexShaderPtr createVertexShader(const void* shader_byte_code, size_t byte_code_size);
		PixelShaderPtr createPixelShader(const void* shader_byte_code, size_t byte_code_size);

		bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

		void releaseCompiledShader();
		void setRasterizerState(bool cullFront);

	private:
		void initRasterizerState();
};

