#pragma once
#include "PrimitivesInclude.h"

#include "Primitive.h"

class Cylinder : public Primitive
{
	protected:
		float height = 2.0f;
		int slices = 32;
		float radius = 1.0f;
		float stacks = 1.0f;
		Vector4 color = WHITE;

	public:
		Cylinder(std::string name, bool blending, OBJECT_TYPE type = CYLINDER);
		~Cylinder();

	protected:
		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
};

