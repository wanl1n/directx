#pragma once
#include "Cube.h"
#include "Math.h"

class Plane : public Cube
{
	private:
		float height = 0.2f;
	public:
		Plane(std::string name, bool blending, OBJECT_TYPE type = PLANE);
		~Plane();

		virtual std::vector<Vertex3D> createVertices() override;
};

