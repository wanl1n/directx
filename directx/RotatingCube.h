#pragma once
#include "Cube.h"
#include "Math.h"

class RotatingCube : public Cube
{
	private:
		Vector3 deltaRot;
		Vector3 rotDir;

		float speed;

	public:
		RotatingCube(std::string name, CubeProps props, bool blending);
		~RotatingCube();

		void update(float deltaTime, RECT viewport);
		void randomizeInit();
};

