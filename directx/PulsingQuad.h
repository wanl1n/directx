#pragma once
#include "Quad.h"

class PulsingQuad : public Quad
{
	public:
		PulsingQuad(std::string name, void* shader_byte_code, size_t size_shader,
				QuadProps props, bool blending);
		~PulsingQuad();

		void update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps);
};

