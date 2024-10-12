#include "RotatingPlane.h"

RotatingPlane::RotatingPlane(std::string name, PlaneProps props, bool blending) : Plane(name, props, blending) {
	this->speed = 1;
}

RotatingPlane::~RotatingPlane() {}

void RotatingPlane::update(float deltaTime, RECT viewport)
{
	this->transform.rotation.x += this->speed * deltaTime;

	//// Reset world space matrix.
	cc.world.setIdentity();

	//// Rotate Plane.
	this->rotateX(this->transform.rotation.x);

	//// Move back to actual position.
	//Matrix4x4 pos;
	//pos.setTranslation(this->transform.position);
	//this->cc.world *= pos;

	// Project
	Plane::update(deltaTime, viewport);
}