#pragma once
#include "Quad.h"

class Area51 : public Quad
{
	private:
		Vector3 position;
		Vector3 direction;

	public:
		Area51(std::string name, QuadProps props, bool blending);
		~Area51();

		void update(float deltaTime, RECT viewport);

		void checkBounds();

		void randomizeInit();
};

