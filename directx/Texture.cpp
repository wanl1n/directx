#include "Texture.h"
#include <exception>
#include "DirectXTex.h"
#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* path) : Resource(path)
{
	DirectX::ScratchImage imgData;

	HRESULT res = DirectX::LoadFromWICFile(path, DirectX::WIC_FLAGS_NONE, nullptr, imgData);

	if (SUCCEEDED(res)) {
		res = DirectX::CreateTexture(GraphicsEngine::get()->getRenderSystem()->d3dDevice, 
									imgData.GetImages(), 
									imgData.GetImageCount(), 
									imgData.GetMetadata(),
									&texture);

		this->width = imgData.GetMetadata().width;
		this->height = imgData.GetMetadata().height;

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imgData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = imgData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::get()->getRenderSystem()->d3dDevice->CreateShaderResourceView(
			texture, &desc, &shaderResView );
	}
	else {
		throw std::exception("Failed to load image data.");
	}
}

Texture::~Texture()
{
	this->shaderResView->Release();
	this->texture->Release();
}

ID3D11ShaderResourceView* Texture::getShaderResView()
{
	return this->shaderResView;
}

float Texture::getWidth()
{
	return this->width;
}

float Texture::getHeight()
{
	return this->height;
}
