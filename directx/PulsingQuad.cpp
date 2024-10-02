#include "PulsingQuad.h"

PulsingQuad::PulsingQuad(std::string name, void* shader_byte_code, size_t size_shader,
	QuadProps props, bool blending) : Quad(name, shader_byte_code, size_shader, props, blending) {}

PulsingQuad::~PulsingQuad() {}

void PulsingQuad::update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps)
{
	// Pulsing Animation
	this->scale(Vector3(0));

	Quad::update(deltaTime, viewport, vs, ps);
}
