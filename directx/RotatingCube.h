#pragma once
#include "Cube.h"
#include "Math.h"

class RotatingCube : public Cube
{
	private:
		Vector3 deltaRot;

	public:
		RotatingCube(std::string name, CubeVertex props, bool blending);
		~RotatingCube();

		void update(float deltaTime, RECT viewport);
		void randomizeInit();
};

