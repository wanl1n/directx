#pragma once
#include "PrimitivesInclude.h"
#include "Primitive.h"

class Plane : public Primitive
{ 
	protected:
		Vector3 center;
		Vector4 color;
		float height;
		float width;

	public:
		Plane(std::string name, PlaneProps props, bool blending);
		~Plane();

		virtual void update(float deltaTime, RECT viewport) override;
		virtual void draw() override;
		bool release();

		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
};

