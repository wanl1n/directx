#pragma once
#include "Cube.h"

class RotatingCube : public Cube
{
	public:
		RotatingCube(std::string name, CubeVertex props, bool blending);
		~RotatingCube();

		void update(float deltaTime, RECT viewport);
};

