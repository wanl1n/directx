#include "BlendState.h"
#include "GraphicsEngine.h"
#include "iostream"

BlendState::BlendState() {}

BlendState::~BlendState() {}

void BlendState::release()
{
	if (bs) this->bs->Release();
	delete this;
}

bool BlendState::init(bool blending)
{
	D3D11_BLEND_DESC desc = {};

	if (blending) {
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = true;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	else {
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateBlendState(&desc, &this->bs)))
		return false;
	return true;
}
