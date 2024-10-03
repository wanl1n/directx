#include "Area51.h"

Area51::Area51(std::string name, QuadProps props, bool blending) : Quad(name, props, blending) {}

Area51::~Area51() {}

void Area51::update(float deltaTime, RECT viewport)
{
	// Move Up Indefinitely
	this->translate(Vector3(0, 0.00001f, 0));

	Quad::update(deltaTime, viewport);
}
