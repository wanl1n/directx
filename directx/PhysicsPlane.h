#pragma once
#include "Cube.h"
#include "Math.h"

class PhysicsPlane : public Cube
{
	public:
		PhysicsPlane(std::string name, bool blending);
		~PhysicsPlane();
		 
		virtual std::vector<Vertex3D> createVertices() override;
};

