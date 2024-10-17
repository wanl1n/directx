#include "PixelShader.h"
#include "RenderSystem.h"

PixelShader::PixelShader(RenderSystem* system) : system(system) {}

PixelShader::~PixelShader() {}

void PixelShader::release()
{
	this->m_ps->Release();
	delete this;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(system->d3dDevice->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		return false;

	return true;
}
