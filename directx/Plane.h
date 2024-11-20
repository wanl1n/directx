#pragma once
#include "PrimitivesInclude.h"
#include "Primitive.h"

class Plane : public Primitive
{ 
	protected:
		Vector4 color = WHITE;
		float height = 1.0f;
		float width = 1.0f;

	public:
		Plane(std::string name, bool blending, OBJECT_TYPE type = PLANE);
		~Plane();

		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
		virtual Math::Vector3 getScale() override;
};

