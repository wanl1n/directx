#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

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
		
		ID3DBlob* m_blob = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;
		friend class ConstantBuffer;
		friend class VertexShader;
		friend class PixelShader;

	public:
		GraphicsEngine();
		~GraphicsEngine();

		bool init();
		bool release();

	public:
		SwapChain* createSwapChain();
		DeviceContext* getImmediateDeviceContext();
		VertexBuffer* createVertexBuffer();
		ConstantBuffer* createConstantBuffer();

		// Shaders
		VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
		PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

		bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		
		void releaseCompiledShader();

	public:
		static GraphicsEngine* get();
};

