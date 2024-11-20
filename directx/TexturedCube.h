#pragma once
#include "Cube.h"

class TexturedCube : public Cube
{
	private:
		TexturePtr texture;

	public:
		TexturedCube(std::string name, bool blending, OBJECT_TYPE type = TEXTURED_CUBE);
		~TexturedCube();	

		virtual void draw() override;
};

