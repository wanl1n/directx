#include "RotatingPlane.h"

RotatingPlane::RotatingPlane(std::string name, PlaneProps props, bool blending) : Plane(name, props, blending) {
	this->speed = 1;

	this->transform.position = Vector3(0);
	cc.world.setScale(Vector3(1));
	cc.world.setTranslation(this->transform.position);
}

RotatingPlane::~RotatingPlane() {}

void RotatingPlane::update(float deltaTime, RECT viewport)
{
	this->transform.rotation.x += this->speed * deltaTime;

	// Reset world space matrix.
	cc.world.setIdentity();

	// Rotate Plane.
	this->rotateX(this->transform.rotation.x);

	// Move back to actual position.
	Matrix4x4 pos;
	pos.setTranslation(this->transform.position);
	this->cc.world *= pos;

	// Project
	Plane::update(deltaTime, viewport);
}