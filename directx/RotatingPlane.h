#pragma once
#include "Plane.h"
#include "Math.h"

class RotatingPlane : public Plane
{
private:
	float speed;

public:
	RotatingPlane(std::string name, PlaneProps props, bool blending);
	~RotatingPlane();

	void update(float deltaTime, RECT viewport);
};

