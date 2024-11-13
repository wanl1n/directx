#pragma once
#include "Cube.h"

class TexturedCube : public Cube
{
	private:
		TexturePtr texture;

	public:
		TexturedCube(std::string name, bool blending, OBJECT_TYPE type = TEXTURED_CUBE);
		~TexturedCube();	

		virtual void initializeBuffers();
		virtual std::vector<Vertex3D> createVertices();
		virtual void draw() override;
};

