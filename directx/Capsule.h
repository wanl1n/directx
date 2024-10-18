#pragma once
#include "PrimitivesInclude.h"

#include "Primitive.h"

class Capsule : public Primitive
{
	protected:
		int rings = 32;
		int sectors = 32;
		float height = 0.5f;
		float radius = 1.0f;
		Vector4 color = WHITE;

	public:
		Capsule(std::string name, bool blending, OBJECT_TYPE type = CAPSULE);
		~Capsule();

	protected:
		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
};

