#pragma once
#include "d3d11.h"
#include <string>
#include <cstdio>
#include <unordered_map>

#include "imgui-master/imgui.h"

#include "Constants.h"

class TextureNames {
	public:
		typedef std::string String;
		const String LOGO = "LOGO";
};

class TextureManager
{
	public:
		static TextureManager* getInstance();
		static void initialize();

		typedef std::string String;
		typedef std::unordered_map<String, TextureData> TextureTable;

	private:
		TextureTable txtTable;

	private:
		TextureManager();
		~TextureManager();
		TextureManager(TextureManager const&) {};
		TextureManager& operator = (TextureManager const&) {};
		static TextureManager* sharedInstance;

		bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
		bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
		
	public:
		TextureData getTexture(String name);
};

