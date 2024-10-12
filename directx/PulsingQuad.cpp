#include "PulsingQuad.h"

PulsingQuad::PulsingQuad(std::string name, QuadProps props, bool blending) : 
	Quad(name, props, blending) {}

PulsingQuad::~PulsingQuad() {}

void PulsingQuad::update(float deltaTime, RECT viewport)
{
	// Pulsing Animation
	cc.m_world.setScale(Vector3::lerp(Vector3(0.5f, 0.5f, 0), Vector3(1, 1, 0), (sin(this->transform.scale.x) + 1.0f) / 2.0f));

	Quad::update(deltaTime, viewport);
}
