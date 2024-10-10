#pragma once
#include "Circle.h"

class BouncingCircle : public Circle
{
private:
	Vector3 position;
	Vector3 direction;

public:
	BouncingCircle(std::string name, CircleProps props, bool blending);
	~BouncingCircle();

	void update(float deltaTime, RECT viewport);

	void checkBounds();

	void randomizeInit();
};

