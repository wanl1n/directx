#include "BlendState.h"
#include "RenderSystem.h"
#include "iostream"
#include <exception>

BlendState::BlendState(bool blending, RenderSystem* system) : system(system)
{
	D3D11_BLEND_DESC desc = {};

	if (blending) {
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = true;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	else {
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	if (!SUCCEEDED(system->d3dDevice->CreateBlendState(&desc, &this->bs)))
		throw std::exception("BlendState creation failed.");
}

BlendState::~BlendState() 
{
	if (bs) this->bs->Release();
}