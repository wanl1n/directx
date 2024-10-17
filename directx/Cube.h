#pragma once
#include "PrimitivesInclude.h"

#include "Primitive.h"

class Cube : public Primitive
{
	protected:
		float side = 0;

	public:
		Cube(std::string name, CubeVertex props, bool blending);
		~Cube();
};

