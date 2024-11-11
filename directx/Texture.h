#pragma once
#include <d3d11.h>
#include "Resource.h"

class DeviceContext;

class Texture : public Resource
{
	private:
		ID3D11Resource* texture = nullptr;
		ID3D11ShaderResourceView* shaderResView = nullptr;

		float width, height;

		friend class DeviceContext;

	public:
		Texture(const wchar_t* path);
		~Texture();

		ID3D11ShaderResourceView* getShaderResView();
		float getWidth();
		float getHeight();
};

