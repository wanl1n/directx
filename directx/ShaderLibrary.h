#pragma once
#include <string>
#include <unordered_map>

#include "Prerequisites.h"

class VertexShader;
class PixelShader;

class ShaderNames {
	public:
		typedef std::wstring String;

		// VertexShader Names
		const String BASE_VERTEX_SHADER_NAME = L"SolidVertexShader.hlsl";
		const String TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";

		// Pixel Shader Names
		const String BASE_PIXEL_SHADER_NAME = L"SolidPixelShader.hlsl";
		const String TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
};

class ShaderLibrary
{
	public:
		class ShaderData {
			public:
				void* shaderByteCode = NULL;
				size_t shaderSize = 0;
		};

		typedef std::wstring String;
		typedef std::unordered_map<String, VertexShaderPtr> VertexShaderTable;
		typedef std::unordered_map<String, PixelShaderPtr> PixelShaderTable;

	private:
		VertexShaderTable activeVertexShaders;
		PixelShaderTable activePixelShaders;

	public:
		static ShaderLibrary* getInstance();
		static void initialize();
		static void destroy();

		// Shader byte code gets dereferenced if stored in a hash table.
		// Request manually.
		void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader);
		VertexShaderPtr getVertexShader(String vertexShaderName);
		PixelShaderPtr getPixelShader(String pixelShaderName);

	private:
		ShaderLibrary();
		~ShaderLibrary();
		ShaderLibrary(ShaderLibrary const&) {};
		ShaderLibrary& operator = (ShaderLibrary const&) {};
		static ShaderLibrary* sharedInstance;
};

