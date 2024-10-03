#pragma once
#include "Quad.h"

class PulsingQuad : public Quad
{
	public:
		PulsingQuad(std::string name, QuadProps props, bool blending);
		~PulsingQuad();

		void update(float deltaTime, RECT viewport);
};

