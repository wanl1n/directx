#include "PulsingQuad.h"

PulsingQuad::PulsingQuad(std::string name, QuadProps props, bool blending) :
	Quad(name, props, blending) {
}

PulsingQuad::~PulsingQuad() {}

void PulsingQuad::update(float deltaTime, RECT viewport)
{
	this->transform.scale.x += deltaTime;
	if (this->transform.scale.x > 20)
		this->transform.scale.x =1;
	// Pulsing Animation
	cc.m_world.setScale(Vector3::lerp(Vector3(0.5f, 0.5f, 0), Vector3(1, 1, 0), (sin(this->transform.scale.x) + 1.0f) / 2.0f));

	// Rotate cube.
	this->transform.rotation.x += deltaTime;
	this->rotateX(this->transform.rotation.x);

	// Move back to actual position.
	Matrix4x4 pos;
	pos.setTranslation(this->transform.position);
	this->cc.m_world *= pos;


	Quad::update(deltaTime, viewport);
}
