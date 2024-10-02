#pragma once
#include "Quad.h"

class Area51 : public Quad
{
public:
	Area51(std::string name, void* shader_byte_code, size_t size_shader,
		QuadProps props, bool blending);
	~Area51();

	void update(float deltaTime, RECT viewport, VertexShader* vs, PixelShader* ps);
};

