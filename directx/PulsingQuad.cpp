#include "PulsingQuad.h"

PulsingQuad::PulsingQuad(std::string name, QuadProps props, bool blending) : 
	Quad(name, props, blending) {}

PulsingQuad::~PulsingQuad() {}

void PulsingQuad::update(float deltaTime, RECT viewport)
{
	// Pulsing Animation
	this->scale(Vector3(0));

	Quad::update(deltaTime, viewport);
}
