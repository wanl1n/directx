#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
	public:
		TextureManager();
		~TextureManager();
	
	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t* path);

	public:
		TexturePtr createTextureFromFile(const wchar_t* path);
};

