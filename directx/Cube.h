#pragma once
#include "PrimitivesInclude.h"

#include "Primitive.h"

class Cube : public Primitive
{
	protected:
		float side = 1.0f;
		Vector4 frontColor = WHITE;
		Vector4 backColor = WHITE;

	public:
		Cube(std::string name, bool blending);
		~Cube();

	protected:
		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
};

