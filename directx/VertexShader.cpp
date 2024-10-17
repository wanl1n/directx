#include "VertexShader.h"
#include "RenderSystem.h"

VertexShader::VertexShader(RenderSystem* system) : system(system) {}

VertexShader::~VertexShader() {}

void VertexShader::release()
{
	this->m_vs->Release();
	delete this;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(system->d3dDevice->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		return false;

	return true;
}
