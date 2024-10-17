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
		SwapChain* createSwapChain(HWND hwnd, UINT width, UINT height);
		DeviceContext* getImmediateDeviceContext();

		VertexBuffer* createVertexBuffer(void* vertices, UINT vertexSize, UINT listSize, void* sbc, UINT bsSize);
		VertexBuffer* createVertexBuffer(std::vector<Vertex3D> vertices, UINT vertexSize, void* sbc, UINT bsSize);
		ConstantBuffer* createConstantBuffer(void* buffer, UINT size_buffer);
		IndexBuffer* createIndexBuffer(void* list_indices, UINT size_list);
		IndexBuffer* createIndexBuffer(std::vector<unsigned int> indices);

		BlendState* createBlendState(bool blending);

		// Shaders
		VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
		PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

		bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

		void releaseCompiledShader();
};

