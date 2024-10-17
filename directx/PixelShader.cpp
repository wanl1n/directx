#include "PixelShader.h"
#include "RenderSystem.h"
#include <exception>

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system) : system(system) 
{
	if (!SUCCEEDED(system->d3dDevice->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		throw std::exception("PixelShader creation failed.");
}

PixelShader::~PixelShader() 
{
	this->m_ps->Release();
}