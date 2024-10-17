#include "VertexShader.h"
#include "RenderSystem.h"
#include <exception>

VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system) : system(system) 
{
	if (!SUCCEEDED(system->d3dDevice->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		throw std::exception("VertexShader creation failed.");
}

VertexShader::~VertexShader() 
{
	this->m_vs->Release();
}