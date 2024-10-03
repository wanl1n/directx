#pragma once
#include "Cube.h"

class RotatingCube : public Cube
{
	public:
		RotatingCube(std::string name, CubeVertex props, bool blending);
		~RotatingCube();

		void update(float deltaTime, RECT viewport,
			Vector3 translate = Vector3(0), Vector3 rotate = Vector3(0), Vector3 scale = Vector3(0));
};

