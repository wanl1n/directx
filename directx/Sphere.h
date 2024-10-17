#pragma once
#include "PrimitivesInclude.h"

#include "Primitive.h"

class Sphere : public Primitive
{
	protected:
		int rings = 32;
		int sectors = 32;
		float radius = 1.0f;
		Vector4 color = WHITE;

	public:
		Sphere(std::string name, bool blending, OBJECT_TYPE type = SPHERE);
		~Sphere();

	protected:
		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
};

