#pragma once
#include "Cube.h"
#include "Math.h"

class PhysicsPlane : public Cube
{
private:
	float height = 0.2f;
	public:
		PhysicsPlane(std::string name, bool blending);
		~PhysicsPlane();
		 
		virtual std::vector<Vertex3D> createVertices() override;
		virtual Math::Vector3 getPosition() override;
		virtual Math::Vector3 getRotation() override;
};

