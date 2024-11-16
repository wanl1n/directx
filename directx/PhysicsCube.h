#pragma once
#include "Cube.h"
#include "Math.h"

class PhysicsCube : public Cube
{
	public:
		PhysicsCube(std::string name, bool blending);
		~PhysicsCube();
};

